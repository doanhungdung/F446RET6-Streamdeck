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
#if !LV_USE_ST7789
#error "LV_USE_ST7789 dang bang 0"
#endif
#if !LV_USE_GENERIC_MIPI
#error "LV_USE_GENERIC_MIPI dang bang 0"
#endif
extern SPI_HandleTypeDef hspi1;

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

/* ---- Send a short command (blocking) ---------------------------------- */
static void lcd_send_cmd(lv_display_t *d, const uint8_t *cmd, size_t cmd_size,
                         const uint8_t *param, size_t param_size)
{
    LV_UNUSED(d);

    CS_LOW();
    DC_CMD();
    HAL_SPI_Transmit(&hspi1, (uint8_t *)cmd, (uint16_t)cmd_size, HAL_MAX_DELAY);

    if (param_size > 0) {
        DC_DATA();
        HAL_SPI_Transmit(&hspi1, (uint8_t *)param, (uint16_t)param_size, HAL_MAX_DELAY);
    }
    CS_HIGH();
}

/* ---- Send pixel data (DMA, runs in background) ------------------------ */
static void lcd_send_color(lv_display_t *d, const uint8_t *cmd, size_t cmd_size,
                           uint8_t *param, size_t param_size)
{
    LV_UNUSED(d);

    /* HAL_SPI_Transmit_DMA takes a uint16_t size: max 65535 bytes.
     * The partial buffers above (11520 bytes) are well below that. */
    LV_ASSERT(param_size <= 65535);

    CS_LOW();
    DC_CMD();
    HAL_SPI_Transmit(&hspi1, (uint8_t *)cmd, (uint16_t)cmd_size, HAL_MAX_DELAY);

    DC_DATA();

    /* LVGL renders RGB565 little-endian, the panel expects big-endian */
    lv_draw_sw_rgb565_swap(param, param_size / 2);

    HAL_SPI_Transmit_DMA(&hspi1, param, (uint16_t)param_size);
    /* CS is released and flush_ready is called in the DMA complete callback */
}

/* ---- DMA complete: release CS and tell LVGL the flush is done --------- */
/* Only ONE definition of this callback may exist in the whole project.
 * If you already have one (e.g. for another SPI device), merge them. */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    if (hspi == &hspi1) {
        CS_HIGH();
        lv_display_flush_ready(disp);
    }
}

/* ---- Public API ------------------------------------------------------- */
void lcd_init(void)
{
    /* Hardware reset */
    RST_LOW();
    HAL_Delay(20);
    RST_HIGH();
    HAL_Delay(120);

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
