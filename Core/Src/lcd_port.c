/**
 * lcd_port.c
 * LVGL 9.2 built-in ST7789 driver on STM32F446RET6 (HAL, SPI1 + DMA TX)
 *
 * CubeMX requirements:
 *   - SPI1: Transmit Only Master, 8 bit, MSB first, CPOL High / CPHA 2 Edge (mode 3)
 *           (try mode 0 if the screen stays blank), prescaler /4 first, then /2
 *   - DMA : SPI1_TX, Normal mode, memory increment ON, byte width, DMA IRQ enabled
 *   - GPIO outputs labeled: CS, DC, RST (CubeMX generates CS_Pin, CS_GPIO_Port, ...)
 *     If your labels differ, edit the pin macros below.
 *
 * lv_conf.h requirements:
 *   #define LV_COLOR_DEPTH 16
 *   #define LV_USE_ST7789  1
 *
 * NOTE: check the typedefs lv_lcd_send_cmd_cb_t / lv_lcd_send_color_cb_t in
 * lv_lcd_generic_mipi.h of your LVGL version. In 9.2 the callbacks return void
 * (as far as I know); newer versions return int32_t. Adjust the return type
 * of lcd_send_cmd() / lcd_send_color() below to match (and add "return 0;").
 */
#include "src/drivers/display/st7789/lv_st7789.h"
#include "src/drivers/display/lcd/lv_lcd_generic_mipi.h"
#include "lcd_port.h"
#include "main.h"
#include "lvgl.h"

/* Toàn bộ SPI1 + DMA2_Stream3 (TX) được điều khiển trực tiếp bằng thanh ghi
 * trong file này. KHÔNG dùng hspi1/hdma_spi1_tx và các hàm HAL_SPI_HAL_DMA
 nữa -> nhớ BỎ lời gọi MX_SPI1_Init() trong main.c (xem ghi chú cuối file). */

/* ---- Display configuration ------------------------------------------- */
#define LCD_W          240
#define LCD_H          240
#define LCD_BUF_LINES  24                          /* partial buffer height */
#define LCD_BUF_SIZE   (LCD_W * LCD_BUF_LINES * 2) /* RGB565 = 2 bytes/px   */

/* ---- Pin helpers ------------------------------------------------------ */
/* Names come from the GPIO labels set in CubeMX (see main.h): CS, DC, RST */
#define CS_LOW()    HAL_GPIO_WritePin(CS_GPIO_Port,  CS_Pin,  GPIO_PIN_RESET)
#define CS_HIGH()   HAL_GPIO_WritePin(CS_GPIO_Port,  CS_Pin,  GPIO_PIN_SET)
#define DC_CMD()    HAL_GPIO_WritePin(DC_GPIO_Port,  DC_Pin,  GPIO_PIN_RESET)
#define DC_DATA()   HAL_GPIO_WritePin(DC_GPIO_Port,  DC_Pin,  GPIO_PIN_SET)
#define RST_LOW()   HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)
#define RST_HIGH()  HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)

/* ---- Internal state --------------------------------------------------- */
static lv_display_t *disp;
static uint8_t buf1[LCD_BUF_SIZE] __attribute__((aligned(4)));
static uint8_t buf2[LCD_BUF_SIZE] __attribute__((aligned(4)));

#define SPI1_DMA_STREAM   DMA2_Stream3   /* SPI1_TX -> DMA2 Stream3 Channel3 (cố định trên F446) */
#define SPI1_DMA_CHANNEL  3UL

/* =========================================================================
 * SPI1 + DMA2_Stream3, cấu hình bằng thanh ghi (thay cho HAL_SPI_Init /
 * HAL_SPI_MspInit / HAL_DMA_Init trong CubeMX).
 * Chân: PA5 = SPI1_SCK, PA7 = SPI1_MOSI (AF5). Không dùng MISO vì driver
 * chỉ truyền (transmit-only) tới màn hình.
 * ========================================================================= */

/* ---- GPIO PA5/PA7 sang chế độ Alternate Function AF5 (SPI1) ----------- */
static void spi1_gpio_init(void)
{
    /* Clock GPIOA đã được bật ở MX_GPIO_Init() trong main.c (AHB1ENR bit 0) */

    GPIOA->MODER   &= ~((0x3UL << (5 * 2)) | (0x3UL << (7 * 2)));
    GPIOA->MODER   |=  ((0x2UL << (5 * 2)) | (0x2UL << (7 * 2)));   /* 10b = AF */

    GPIOA->OTYPER  &= ~((1UL << 5) | (1UL << 7));                  /* push-pull */

    GPIOA->OSPEEDR |=  ((0x3UL << (5 * 2)) | (0x3UL << (7 * 2)));  /* very high speed, giống CubeMX */

    GPIOA->PUPDR   &= ~((0x3UL << (5 * 2)) | (0x3UL << (7 * 2)));  /* không kéo */

    /* AFR[0] = AFRL, chân 0..7, mỗi chân 4 bit. AF5 = 0101b = SPI1 */
    GPIOA->AFR[0]  &= ~((0xFUL << (5 * 4)) | (0xFUL << (7 * 4)));
    GPIOA->AFR[0]  |=  ((0x5UL << (5 * 4)) | (0x5UL << (7 * 4)));
}

/* ---- SPI1 CR1/CR2 (thay HAL_SPI_Init) ---------------------------------- */
static void spi1_init(void)
{
    RCC->APB2ENR |= (1UL << 12);      /* SPI1EN: SPI1 nằm trên APB2 */
    (void)RCC->APB2ENR;

    spi1_gpio_init();

    /* CPOL=0, CPHA=0 (mode 1EDGE/LOW giống cấu hình cũ), BR=000 (fPCLK/2),
     * LSBFIRST=0 (MSB trước), DFF=0 (8-bit), CRCEN=0 -> đều là giá trị 0 sau reset,
     * chỉ cần set các bit khác 0 dưới đây. */
    SPI1->CR1 = (1UL << 2)            /* MSTR = 1: Master                         */
              | (1UL << 8)            /* SSI  = 1: bắt buộc khi SSM=1 ở chế độ Master */
              | (1UL << 9);           /* SSM  = 1: quản lý chân NSS bằng phần mềm  */

    SPI1->CR2 = (1UL << 1);           /* TXDMAEN = 1: cho phép DMA yêu cầu khi TXE */

    /* ---- DMA2_Stream3 cho SPI1_TX: các trường cố định, cấu hình 1 lần ---- */
    SPI1_DMA_STREAM->CR &= ~(1UL << 0);            /* tắt stream trước khi sửa   */
    while (SPI1_DMA_STREAM->CR & (1UL << 0));      /* chờ tắt hẳn (bit EN về 0)  */

    SPI1_DMA_STREAM->PAR = (uint32_t)&SPI1->DR;    /* địa chỉ ngoại vi: DR của SPI1, cố định */

    SPI1->CR1 |= (1UL << 6);          /* SPE = 1: bật SPI1, làm SAU CÙNG */
}

/* ---- Gửi lệnh/tham số ngắn, kiểu chặn (blocking, thay HAL_SPI_Transmit) - */
static void spi1_transmit_blocking(const uint8_t *data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++) {
        while (!(SPI1->SR & (1UL << 1)));   /* chờ TXE = 1 (bộ đệm truyền rỗng) */
        SPI1->DR = data[i];
    }
    while (!(SPI1->SR & (1UL << 1)));       /* chờ byte cuối rời khỏi bộ đệm    */
    while (SPI1->SR & (1UL << 7));          /* chờ BSY = 0 (SPI thật sự rảnh)   */
}

/* ---- Gửi màu bằng DMA (thay HAL_SPI_Transmit_DMA) ---------------------- */
static void spi1_transmit_dma(uint8_t *data, uint16_t size)
{
    SPI1_DMA_STREAM->CR &= ~(1UL << 0);       /* tắt stream để nạp lại NDTR/M0AR */
    while (SPI1_DMA_STREAM->CR & (1UL << 0));

    /* xoá hết cờ cũ của stream3 (TCIF3/HTIF3/TEIF3/DMEIF3/FEIF3) trong LIFCR */
    DMA2->LIFCR = (1UL << 27) | (1UL << 26) | (1UL << 25) | (1UL << 24) | (1UL << 22);

    SPI1_DMA_STREAM->M0AR = (uint32_t)data;
    SPI1_DMA_STREAM->NDTR = size;

    SPI1_DMA_STREAM->CR = (SPI1_DMA_CHANNEL << 25)  /* CHSEL  = kênh 3           */
                        | (0x0UL << 16)              /* PL     = ưu tiên thấp     */
                        | (0x0UL << 13)              /* MSIZE  = byte             */
                        | (0x0UL << 11)              /* PSIZE  = byte             */
                        | (1UL   << 10)              /* MINC   = tăng địa chỉ bộ nhớ */
                        | (0x0UL << 9)               /* PINC   = không tăng địa chỉ ngoại vi */
                        | (0x0UL << 8)               /* CIRC   = 0: không lặp vòng */
                        | (0x1UL << 6)                /* DIR    = 01b: bộ nhớ -> ngoại vi */
                        | (1UL   << 4);              /* TCIE   = 1: ngắt khi truyền xong */

    SPI1_DMA_STREAM->CR |= (1UL << 0);              /* EN = 1: bắt đầu truyền */
}

/* ---- Ngắt DMA2_Stream3: báo LVGL đã gửi xong 1 mảng màu ----------------
 * Vì không dùng HAL_DMA nữa, hàm này THAY THẾ HOÀN TOÀN handler mặc định.
 * -> Trong stm32f4xx_it.c phải XOÁ/COMMENT hàm DMA2_Stream3_IRQHandler() cũ
 *    (bản gọi HAL_DMA_IRQHandler(&hdma_spi1_tx)), nếu không sẽ bị lỗi linker
 *    "multiple definition". */
void DMA2_Stream3_IRQHandler(void)
{
    if (DMA2->LISR & (1UL << 27)) {           /* TCIF3: stream3 truyền xong */
        DMA2->LIFCR = (1UL << 27);            /* xoá cờ TCIF3 */
        CS_HIGH();
        lv_display_flush_ready(disp);
    }
}

/* ---- Send a short command (blocking) ---------------------------------- */
static void lcd_send_cmd(lv_display_t *d, const uint8_t *cmd, size_t cmd_size,
                         const uint8_t *param, size_t param_size)
{
    LV_UNUSED(d);

    CS_LOW();
    DC_CMD();
    spi1_transmit_blocking(cmd, (uint16_t)cmd_size);

    if (param_size > 0) {
        DC_DATA();
        spi1_transmit_blocking(param, (uint16_t)param_size);
    }
    CS_HIGH();
}

/* ---- Send pixel data (DMA, runs in background) ------------------------ */
static void lcd_send_color(lv_display_t *d, const uint8_t *cmd, size_t cmd_size,
                           uint8_t *param, size_t param_size)
{
    LV_UNUSED(d);

    /* NDTR là thanh ghi 16-bit -> tối đa 65535 byte/lần. Buffer partial ở trên
     * (11520 byte) nằm dưới giới hạn này rất nhiều. */
    LV_ASSERT(param_size <= 65535);

    CS_LOW();
    DC_CMD();
    spi1_transmit_blocking(cmd, (uint16_t)cmd_size);

    DC_DATA();

    /* LVGL renders RGB565 little-endian, the panel expects big-endian */
    lv_draw_sw_rgb565_swap(param, param_size / 2);

    spi1_transmit_dma(param, (uint16_t)param_size);
    /* CS được nhả và flush_ready được gọi trong DMA2_Stream3_IRQHandler() ở trên */
}

/* ---- Public API ------------------------------------------------------- */
void lcd_init(void)
{
    /* Hardware reset */
    RST_LOW();
    HAL_Delay(200);
    RST_HIGH();
    HAL_Delay(1500);

    /* SPI1 + DMA2_Stream3, bằng thanh ghi -> thay cho MX_SPI1_Init() cũ.
     * XOÁ lời gọi MX_SPI1_Init() (và định nghĩa của nó) khỏi main.c. */
    spi1_init();

    /* LVGL core */
    lv_init();
    lv_tick_set_cb(HAL_GetTick);

    /* ST7789 driver from LVGL */
    disp = lv_st7789_create(LCD_W, LCD_H, LV_LCD_FLAG_NONE,
                            lcd_send_cmd, lcd_send_color);

    /* Most 240x240 IPS ST7789 modules need color inversion ON */
    lv_lcd_generic_mipi_set_invert(disp, true);

    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
}
