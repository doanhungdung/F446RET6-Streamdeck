/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_hid.h"
#include "lvgl.h"
#include "lcd_port.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NUM_BUTTONS   6u   /* PC0 -> PC5 */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/* USER CODE BEGIN PV */
static uint8_t btn_last = 0xFF;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
static void Buttons_Init(void);
static uint8_t Buttons_Scan(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* ============================================================================
 *  1. ẢNH HIỂN THỊ TRÊN MÀN HÌNH
 *
 *  Muốn thêm / bớt ảnh chỉ cần sửa 2 chỗ: dòng "extern" và bảng image_table[].
 *  Tên biến ảnh (hcmute_pixel, hcmute_dore...) phải trùng với tên trong file .c đã convert.
 * ========================================================================== */
extern const lv_image_dsc_t hcmute_logo;   /* hcmute_logo.c  */
extern const lv_image_dsc_t hcmute_pixel;  /* hcmute_pixel.c */
extern const lv_image_dsc_t hcmute_dore;   /* hcmute_dore.c  */

static const lv_image_dsc_t *const image_table[] = {
    &hcmute_logo,
    &hcmute_pixel,
    &hcmute_dore,
};
#define IMAGE_COUNT  (sizeof(image_table) / sizeof(image_table[0]))

static lv_obj_t *image_obj   = NULL;   /* đối tượng LVGL đang hiển thị ảnh          */
static uint8_t   image_index = 0;      /* ảnh đang hiển thị; sau khi ấn giữ = ảnh đã lưu */

/**
  * @brief  Chuyển sang ảnh kế tiếp (step > 0) hoặc ảnh trước đó (step < 0).
  *         Quay vòng: ảnh cuối -> ảnh đầu và ngược lại.
  */
static void Image_Change(int8_t step)
{
    if (step > 0)
        image_index = (uint8_t)((image_index + 1U) % IMAGE_COUNT);
    else
        image_index = (uint8_t)((image_index + IMAGE_COUNT - 1U) % IMAGE_COUNT);

    lv_image_set_src(image_obj, image_table[image_index]);
}

/* ============================================================================
 *  2. USB HID (bàn phím + phím media)
 * ========================================================================== */
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t HID_Buffer[8] = {0};   /* giữ lại phòng file khác có extern */

/* Modifier bits của keyboard report */
#define MOD_CTRL   0x01
#define MOD_SHIFT  0x02
#define MOD_ALT    0x04
#define MOD_GUI    0x08   /* phím Windows */

/* Keycode (USB HID usage) của các phím đang dùng */
#define KEY_A      0x04
#define KEY_C      0x06
#define KEY_D      0x07
#define KEY_E      0x08
#define KEY_L      0x0F
#define KEY_M      0x10
#define KEY_R      0x15
#define KEY_S      0x16
#define KEY_U      0x18
#define KEY_V      0x19
#define KEY_ENTER  0x28

/* Bit trong Consumer report (Report ID 2) */
#define VOL_INC_BIT     (1u << 0)
#define VOL_DEC_BIT     (1u << 1)
#define VOL_MUTE_BIT    (1u << 2)
#define BRIGHT_INC_BIT  (1u << 3)
#define BRIGHT_DEC_BIT  (1u << 4)

/* Chờ USB rảnh trước khi gửi report tiếp theo */
static void HID_WaitReady(void)
{
    USBD_HID_HandleTypeDef *hhid;
    uint32_t deadline = HAL_GetTick() + 20;   /* timeout an toàn, tránh treo vô hạn nếu USB rớt */

    do {
        hhid = (USBD_HID_HandleTypeDef *)hUsbDeviceFS.pClassDataCmsit[0];
    } while (hhid != NULL && hhid->state != USBD_HID_IDLE && HAL_GetTick() < deadline);
}

/* Gửi 1 tổ hợp phím (nhấn rồi nhả). Bấm 1 phím thường thì truyền mod = 0. */
static void HID_Keyboard_Combo(uint8_t mod, uint8_t keycode)
{
    uint8_t report[9] = {0};
    report[0] = 0x01;          /* Report ID keyboard */
    report[1] = mod;
    report[3] = keycode;

    HID_WaitReady();
    USBD_HID_SendReport(&hUsbDeviceFS, report, sizeof(report));

    HAL_Delay(10);             /* giữ phím đủ lâu để Windows nhận combo */
    report[1] = 0;
    report[3] = 0;

    HID_WaitReady();
    USBD_HID_SendReport(&hUsbDeviceFS, report, sizeof(report));
}

/* Bấm 1 phím đơn (không có modifier) */
#define HID_Key(keycode)   HID_Keyboard_Combo(0, (keycode))

/* Gửi 1 phím media (âm lượng / độ sáng): nhấn rồi nhả */
static void HID_Consumer_Press(uint8_t bitmask)
{
    uint8_t report[2];
    report[0] = 0x02;          /* Report ID consumer */
    report[1] = bitmask;

    HID_WaitReady();
    USBD_HID_SendReport(&hUsbDeviceFS, report, sizeof(report));

    HAL_Delay(2);
    report[1] = 0;

    HID_WaitReady();
    USBD_HID_SendReport(&hUsbDeviceFS, report, sizeof(report));
}

/* ============================================================================
 *  3. 6 NÚT NHẤN PC0..PC5
 * ========================================================================== */

/**
  * @brief  Cấu hình PC0..PC5 làm ngõ vào (Input, Pull-up) bằng thao tác thanh ghi trực tiếp.
  *         Dùng phép dịch bit (<<) để chọn đúng vị trí 2 bit (MODER/PUPDR) hoặc 1 bit (IDR)
  *         tương ứng với từng chân.
  */
static void Buttons_Init(void)
{
  uint8_t pin;

  /* 1. Bật clock cho GPIOC: bit 2 của AHB1ENR ứng với GPIOCEN */
  RCC->AHB1ENR |= (1UL << 2);

  for (pin = 0; pin < NUM_BUTTONS; pin++)
  {
    /* 2. MODER: mỗi chân chiếm 2 bit, vị trí bit = pin*2
     *    Input mode = 00b -> XÓA 2 bit bằng AND với đảo mask (KHÔNG dùng |= để xóa,
     *    vì |= chỉ có thể SET bit lên 1, không thể clear bit về 0).
     */
    GPIOC->MODER &= ~(0x3UL << (pin * 2U));

    /* 3. PUPDR: mỗi chân chiếm 2 bit -> Pull-up = 01b
     *    Bước a: xóa 2 bit cũ về 00b
     *    Bước b: SET bit thấp lên 1 bằng |= để có 01b (Pull-up)
     */
    GPIOC->PUPDR &= ~(0x3UL << (pin * 2U));
    GPIOC->PUPDR |=  (0x1UL << (pin * 2U));
  }
}

/**
  * @brief  Quét 6 nút PC0..PC5, trả về chỉ số nút đang được nhấn (0..5).
  *         Trả về 0xFF nếu không có nút nào được nhấn.
  *         Nút nối GND khi nhấn (active LOW) nên đọc IDR == 0 nghĩa là đang nhấn.
  */
static uint8_t Buttons_Scan(void)
{
  uint8_t pin;

  for (pin = 0; pin < NUM_BUTTONS; pin++)
  {
    /* Kiểm tra bit tương ứng trong thanh ghi IDR bằng phép dịch bit (1UL << pin) */
    if ((GPIOC->IDR & (1UL << pin)) == 0UL)
    {
      return pin;
    }
  }

  return 0xFF;
}

/* Hành động của từng nút */
static void Button_Action(uint8_t idx)
{
    switch (idx)
    {
    case 0: HID_Keyboard_Combo(MOD_CTRL, KEY_C); break;               /* PC0: Ctrl+C */
    case 1: HID_Keyboard_Combo(MOD_CTRL, KEY_V); break;               /* PC1: Ctrl+V */
    case 2: HID_Keyboard_Combo(MOD_GUI | MOD_SHIFT, KEY_S); break;    /* PC2: Win+Shift+S */

    case 3:                                                           /* PC3: mở cmd */
        HID_Keyboard_Combo(MOD_GUI, KEY_R);  /* Win+R */
        HAL_Delay(400);                      /* chờ hộp thoại Run hiện ra */
        HID_Key(KEY_C);
        HID_Key(KEY_M);
        HID_Key(KEY_D);
        HID_Key(KEY_ENTER);
        break;

    case 4:                                                           /* PC4: mở app Claude */
        HID_Keyboard_Combo(MOD_GUI, 0);      /* bấm Win: mở Start */
        HAL_Delay(500);                      /* chờ Start hiện ra */
        HID_Key(KEY_C);
        HID_Key(KEY_L);
        HID_Key(KEY_A);
        HID_Key(KEY_U);
        HID_Key(KEY_D);
        HID_Key(KEY_E);
        HAL_Delay(400);                      /* chờ Windows tìm ra kết quả */
        HID_Key(KEY_ENTER);
        break;

    case 5: HID_Keyboard_Combo(MOD_CTRL, KEY_D); break;               /* PC5: Ctrl+D */
    }
}

/* Chỉ gửi phím 1 lần khi nút VỪA ĐƯỢC NHẤN (trạng thái thay đổi), không lặp khi đang giữ */
static void Buttons_Handle(void)
{
    uint8_t btn = Buttons_Scan();

    if (btn != btn_last)
    {
        if (btn != 0xFF)
        {
            Button_Action(btn);
        }
        btn_last = btn;
    }
}

/* ============================================================================
 *  4. ENCODER (TIM3) + NÚT NHẤN ENCODER (PC8)
 *
 *  Nút nhấn encoder:
 *    - Ấn 1 lần : Volume <-> Brightness
 *    - Ấn 2 lần : vào chế độ chọn ảnh (xoay encoder để đổi ảnh)
 *    - Ấn giữ   : (đang ở chế độ chọn ảnh) LƯU ảnh đang hiển thị và thoát về Volume
 * ========================================================================== */
#define ENCODER_DIV     4      /* số xung TIM3 ứng với 1 nấc xoay */

#define EB_DEBOUNCE_MS  30u
#define EB_DBL_MS       350u   /* cửa sổ chờ lần nhấn thứ 2 */
#define EB_LONG_MS      800u   /* ngưỡng nhấn giữ */

typedef enum { MODE_VOLUME = 0, MODE_BRIGHTNESS, MODE_IMAGE } app_mode_t;
typedef enum { EB_NONE = 0, EB_SINGLE, EB_DOUBLE, EB_LONG } enc_evt_t;

static app_mode_t app_mode = MODE_VOLUME;
static int16_t enc_last_count = 0;

/* Trả về +1 / -1 khi xoay đủ 1 nấc, 0 nếu chưa đủ */
static int8_t Encoder_ReadStep(void)
{
    int16_t count = (int16_t)TIM3->CNT;   /* đọc thẳng thanh ghi đếm của TIM3 */
    int16_t diff  = count - enc_last_count;
    if (diff >= ENCODER_DIV) { enc_last_count = count; return 1; }
    if (diff <= -ENCODER_DIV) { enc_last_count = count; return -1; }
    return 0;
}

/* Máy trạng thái phân biệt ấn 1 lần / ấn 2 lần / ấn giữ của nút PC8 */
static enc_evt_t Encoder_ButtonEvent(void)
{
    static uint8_t  st = 0;    /* 0 rảnh, 1 đang nhấn lần 1, 2 chờ lần 2, 3 chờ nhả */
    static uint32_t t = 0;
    uint8_t  down = ((GPIOC->IDR & (1UL << 8)) == 0UL);   /* PC8 (ENC_SW), active LOW: bit IDR = 0 -> đang nhấn */
    uint32_t now  = HAL_GetTick();

    switch (st)
    {
    case 0:
        if (down) { st = 1; t = now; }
        break;
    case 1:
        if (!down) {
            st = (now - t >= EB_DEBOUNCE_MS) ? 2 : 0;   /* nhả sớm quá = nhiễu */
            t = now;
        } else if (now - t >= EB_LONG_MS) {
            st = 3;
            return EB_LONG;
        }
        break;
    case 2:
        if (now - t < EB_DEBOUNCE_MS) break;            /* bỏ qua nảy lúc nhả */
        if (down) { st = 3; return EB_DOUBLE; }
        if (now - t >= EB_DBL_MS) { st = 0; return EB_SINGLE; }
        break;
    case 3:
        if (!down) st = 0;
        break;
    }
    return EB_NONE;
}

/* Xử lý sự kiện nút nhấn encoder -> đổi chế độ */
static void Mode_Handle(enc_evt_t e)
{
    switch (e)
    {
    case EB_SINGLE:
        if (app_mode == MODE_VOLUME)          app_mode = MODE_BRIGHTNESS;
        else if (app_mode == MODE_BRIGHTNESS) app_mode = MODE_VOLUME;
        break;

    case EB_DOUBLE:
        if (app_mode == MODE_VOLUME) app_mode = MODE_IMAGE;
        break;

    case EB_LONG:
        /* Lưu ảnh: image_index đang trỏ đúng ảnh đang hiển thị nên chỉ cần thoát chế độ,
         * ảnh sẽ được giữ nguyên trên màn hình. */
        if (app_mode == MODE_IMAGE) app_mode = MODE_VOLUME;
        break;

    default:
        break;
    }
}

/* Xử lý khi xoay encoder: tùy chế độ mà làm việc khác nhau */
static void Encoder_Rotate(int8_t step)
{
    switch (app_mode)
    {
    case MODE_VOLUME:
        HID_Consumer_Press(step > 0 ? VOL_INC_BIT : VOL_DEC_BIT);
        break;
    case MODE_BRIGHTNESS:
        HID_Consumer_Press(step > 0 ? BRIGHT_INC_BIT : BRIGHT_DEC_BIT);
        break;
    case MODE_IMAGE:
        Image_Change(step);
        break;
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();

  /* Nền trắng: nếu ảnh nhỏ hơn 240x240 thì phần viền xung quanh sẽ liền màu với ảnh */
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_white(), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(lv_screen_active(), LV_OPA_COVER, LV_PART_MAIN);

  /* Hiển thị ảnh đầu tiên trong image_table */
  image_obj = lv_image_create(lv_screen_active());
  lv_image_set_src(image_obj, image_table[image_index]);
  lv_obj_center(image_obj);

  Buttons_Init();

  /* Bật encoder TIM3 bằng thanh ghi */
  TIM3->CCER |= (1UL << 0);            /* CC1E = bit 0: bật kênh 1 (PC6) */
  TIM3->CCER |= (1UL << 4);            /* CC2E = bit 4: bật kênh 2 (PC7) */
  TIM3->CR1  |= (1UL << 0);            /* CEN  = bit 0: cho bộ đếm chạy  */
  enc_last_count = (int16_t)TIM3->CNT;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    lv_timer_handler();                    /* cập nhật màn hình LVGL          */

    Buttons_Handle();                      /* 6 nút PC0..PC5                  */
    Mode_Handle(Encoder_ButtonEvent());    /* nút nhấn encoder: đổi chế độ    */

    int8_t step = Encoder_ReadStep();      /* xoay encoder                    */
    if (step != 0)
    {
      Encoder_Rotate(step);
    }

    HAL_Delay(5);
  }
  /* USER CODE END 3 */
}

/**
  * @brief  Cấu hình xung nhịp hệ thống bằng thanh ghi
  *         (thay cho HAL_RCC_OscConfig + HAL_RCC_ClockConfig)
  *
  *         HSE -> PLL (M=4, N=90, P=2, Q=5, R=2) -> SYSCLK = 90 MHz
  *         APB1 = /2
  *         APB2 = /1
  *         Flash = 2 wait state, Voltage Scale 3
  *
  *         Quy ước dùng trong hàm này:
  *           - SET  bit lên 1 : REG |=  (1UL << vị_trí)
  *           - XÓA  bit về 0  : REG &= ~(1UL << vị_trí)
  *           - Trường nhiều bit: xóa cả trường bằng &= ~(mask << vị_trí),
  *             sau đó gán giá trị mới bằng |= (giá_trị << vị_trí)
  */
void SystemClock_Config(void)
{
  /* ===== Bước 1: bật clock cho PWR và chọn Voltage Scale 3 ============== */
  RCC->APB1ENR |= (1UL << 28);          /* PWREN = bit 28 của APB1ENR */
  (void)RCC->APB1ENR;                   /* đọc lại 1 lần để clock kịp ổn định */

  PWR->CR &= ~(0x3UL << 14);            /* xóa 2 bit VOS [15:14] */
  PWR->CR |=  (0x1UL << 14);            /* VOS = 01b -> Scale 3 */

  /* ===== Bước 2: bật HSE (thạch anh ngoài) và chờ ổn định ================ */
  RCC->CR |= (1UL << 16);                   /* HSEON  = bit 16 */
  while ((RCC->CR & (1UL << 17)) == 0UL);   /* chờ HSERDY = bit 17 lên 1 */

  /* ===== Bước 3: cấu hình PLL (phải làm khi PLL đang tắt) ================ */
  RCC->PLLCFGR = (4UL  << 0)    /* PLLM   [5:0]   = 4                       */
               | (90UL << 6)    /* PLLN   [14:6]  = 90                      */
               | (0UL  << 16)   /* PLLP   [17:16] = 00b -> chia 2           */
               | (1UL  << 22)   /* PLLSRC bit 22  = 1   -> nguồn là HSE     */
               | (5UL  << 24)   /* PLLQ   [27:24] = 5                       */
               | (2UL  << 28);  /* PLLR   [30:28] = 2                       */

  /* ===== Bước 4: bật PLL và chờ khóa ===================================== */
  RCC->CR |= (1UL << 24);                   /* PLLON  = bit 24 */
  while ((RCC->CR & (1UL << 25)) == 0UL);   /* chờ PLLRDY = bit 25 lên 1 */

  /* ===== Bước 5: Flash latency = 2 wait state (PHẢI làm trước khi đổi SYSCLK) */
  FLASH->ACR &= ~(0xFUL << 0);              /* xóa LATENCY [3:0] */
  FLASH->ACR |=  (2UL   << 0);              /* LATENCY = 2 */
  while ((FLASH->ACR & 0xFUL) != 2UL);      /* đọc lại để chắc chắn đã nhận */

  /* ===== Bước 6: hệ số chia cho các bus (thanh ghi RCC->CFGR) =========== */
  RCC->CFGR &= ~(0xFUL << 4);               /* HPRE  [7:4]   = 0000b -> AHB  /1 */

  RCC->CFGR &= ~(0x7UL << 10);              /* xóa PPRE1 [12:10] */
  RCC->CFGR |=  (0x4UL << 10);              /* PPRE1 = 100b -> APB1 /2 */

  RCC->CFGR &= ~(0x7UL << 13);              /* PPRE2 [15:13] = 000b -> APB2 /1 */

  /* ===== Bước 7: chọn PLL làm nguồn SYSCLK =============================== */
  RCC->CFGR &= ~(0x3UL << 0);               /* xóa SW [1:0] */
  RCC->CFGR |=  (0x2UL << 0);               /* SW = 10b -> chọn PLL */
  while ((RCC->CFGR & (0x3UL << 2)) != (0x2UL << 2));   /* chờ SWS [3:2] = 10b */

  /* ===== Bước 8: tạo clock 48 MHz cho USB từ PLLSAI (khớp file .ioc) ======
   *  HSE 8 MHz / PLLSAIM(4) = 2 MHz  ->  x PLLSAIN(96) = 192 MHz  ->  / PLLSAIP(4) = 48 MHz
   *  PLLQ của PLL chính chỉ ra 180/5 = 36 MHz nên KHÔNG dùng được cho USB. */
  RCC->PLLSAICFGR &= ~((0x3FUL  << 0)     /* xóa PLLSAIM [5:0]   */
                     | (0x1FFUL << 6)     /* xóa PLLSAIN [14:6]  */
                     | (0x3UL   << 16)    /* xóa PLLSAIP [17:16] */
                     | (0xFUL   << 24));  /* xóa PLLSAIQ [27:24] */
  RCC->PLLSAICFGR |=  ((4UL  << 0)        /* PLLSAIM = 4                          */
                     | (96UL << 6)        /* PLLSAIN = 96                         */
                     | (1UL  << 16)       /* PLLSAIP = 01b -> chia 4              */
                     | (2UL  << 24));     /* PLLSAIQ = 2 (không dùng, giá trị hợp lệ) */

  RCC->DCKCFGR2 |= (1UL << 27);             /* CK48MSEL = bit 27: 1 -> USB lấy 48 MHz từ PLLSAI-P */

  RCC->CR |= (1UL << 28);                   /* PLLSAION  = bit 28 */
  while ((RCC->CR & (1UL << 29)) == 0UL);   /* chờ PLLSAIRDY = bit 29 lên 1 */

  /* ===== Bước 9: báo cho HAL biết tốc độ mới ============================= */
  /* HAL_Init() đã cấu hình SysTick theo xung nhịp HSI 16 MHz cũ.
   * Nếu không cấu hình lại, HAL_GetTick()/HAL_Delay() sẽ chạy nhanh hơn thực tế
   * và LVGL (dùng HAL_GetTick) cũng bị lệch theo. */
  SystemCoreClockUpdate();                  /* cập nhật biến SystemCoreClock */
  HAL_InitTick(TICK_INT_PRIORITY);          /* cấu hình lại SysTick = 1 ms   */
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM3 Initialization Function (viết lại bằng thanh ghi)
  *        TIM3 chạy Encoder Mode TI1&TI2 (đếm cả 2 pha), ARR = 65535, lọc nhiễu = 10.
  *        Hàm này chỉ CẤU HÌNH; việc bật đếm nằm ở USER CODE 2 trong main().
  */
static void MX_TIM3_Init(void)
{
  /* ===== 1. Bật clock cho TIM3 (APB1) ==================================== */
  RCC->APB1ENR |= (1UL << 1);           /* TIM3EN = bit 1 */
  (void)RCC->APB1ENR;

  /* ===== 2. Chân encoder: PC6 = TIM3_CH1, PC7 = TIM3_CH2 (AF2) =========== */
  /* Khớp file .ioc: PC6 -> TIM3_CH1, PC7 -> TIM3_CH2, không kéo lên/xuống.
   * (Clock GPIOC đã được bật trong MX_GPIO_Init) */

  /* MODER: 10b = Alternate Function */
  GPIOC->MODER   &= ~((0x3UL << (6 * 2)) | (0x3UL << (7 * 2)));
  GPIOC->MODER   |=  ((0x2UL << (6 * 2)) | (0x2UL << (7 * 2)));

  /* OTYPER: 0 = push-pull */
  GPIOC->OTYPER  &= ~((1UL << 6) | (1UL << 7));

  /* OSPEEDR: 00b = tốc độ thấp */
  GPIOC->OSPEEDR &= ~((0x3UL << (6 * 2)) | (0x3UL << (7 * 2)));

  /* PUPDR: 00b = không kéo (giống cấu hình CubeMX). Nếu module encoder của bạn
   * không có điện trở kéo lên sẵn thì đổi sang 01b (pull-up). */
  GPIOC->PUPDR   &= ~((0x3UL << (6 * 2)) | (0x3UL << (7 * 2)));

  /* AFR[0] (AFRL) điều khiển chân 0..7, mỗi chân 4 bit -> vị trí = pin * 4
   * AF2 = 0010b = TIM3 */
  GPIOC->AFR[0]  &= ~((0xFUL << (6 * 4)) | (0xFUL << (7 * 4)));
  GPIOC->AFR[0]  |=  ((0x2UL << (6 * 4)) | (0x2UL << (7 * 4)));

  /* ===== 3. Cấu hình phần đếm của TIM3 =================================== */
  TIM3->CR1 = 0;                        /* CKD = 00 (chia 1), ARPE = 0, đếm lên, chưa bật CEN */
  TIM3->CR2 = 0;                        /* MMS = 000: TRGO = Reset (không dùng master mode)   */
  TIM3->PSC = 0;                        /* Prescaler = 0     */
  TIM3->ARR = 65535;                    /* Period    = 65535 */

  /* ===== 4. Chế độ Encoder =============================================== */
  TIM3->SMCR = (0x3UL << 0);            /* SMS [2:0] = 011b: Encoder mode 3 (đếm ở cả TI1 và TI2)
                                           đồng thời MSM = 0 (Master/Slave tắt) */

  /* ===== 5. Kênh 1 và kênh 2 làm ngõ vào (Input Capture) ================= */
  TIM3->CCMR1 = (0x1UL << 0)            /* CC1S   [1:0]   = 01b: IC1 nối với TI1 (direct)  */
              | (0x0UL << 2)            /* IC1PSC [3:2]   = 00b: không chia                */
              | (10UL  << 4)            /* IC1F   [7:4]   = 10 : bộ lọc nhiễu              */
              | (0x1UL << 8)            /* CC2S   [9:8]   = 01b: IC2 nối với TI2 (direct)  */
              | (0x0UL << 10)           /* IC2PSC [11:10] = 00b: không chia                */
              | (10UL  << 12);          /* IC2F   [15:12] = 10 : bộ lọc nhiễu              */

  /* CCER: CC1P (bit 1), CC1NP (bit 3), CC2P (bit 5), CC2NP (bit 7) = 0 -> cạnh lên.
   * CC1E (bit 0) và CC2E (bit 4) để 0 ở đây, sẽ bật khi khởi động encoder. */
  TIM3->CCER = 0;

  /* ===== 6. Nạp giá trị PSC/ARR vào thanh ghi shadow, đưa bộ đếm về 0 ==== */
  TIM3->EGR = (1UL << 0);               /* UG = bit 0: tạo update event */
  TIM3->CNT = 0;
}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable: DMA2EN = bit 22 của AHB1ENR */
  RCC->AHB1ENR |= (1UL << 22);
  (void)RCC->AHB1ENR;

  /* DMA interrupt init */
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

}

/**
  * @brief GPIO Initialization Function (viết lại bằng thanh ghi)
  *
  *  Cách đọc code:
  *   - MODER, OSPEEDR, PUPDR: mỗi chân chiếm 2 bit  -> vị trí bit = số_chân * 2
  *   - OTYPER, ODR, IDR     : mỗi chân chiếm 1 bit  -> vị trí bit = số_chân
  *   - Muốn gán giá trị cho trường 2 bit: XÓA bằng  &= ~(0x3 << vị_trí)
  *     rồi SET bằng  |= (giá_trị << vị_trí)
  *   - Luôn dùng &= và |= (đọc-sửa-ghi), KHÔNG gán bằng dấu "=" để không làm hỏng
  *     cấu hình của các chân khác (ví dụ PA13/PA14 đang là SWD).
  *
  *   MODER : 00 = Input, 01 = Output, 10 = Alternate function, 11 = Analog
  *   PUPDR : 00 = không kéo, 01 = pull-up, 10 = pull-down
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* ===== 1. Bật clock các cổng GPIO (RCC->AHB1ENR) ====================== */
  RCC->AHB1ENR |= (1UL << 0);           /* GPIOAEN = bit 0 */
  RCC->AHB1ENR |= (1UL << 1);           /* GPIOBEN = bit 1 */
  RCC->AHB1ENR |= (1UL << 2);           /* GPIOCEN = bit 2 */
  RCC->AHB1ENR |= (1UL << 7);           /* GPIOHEN = bit 7 (chân thạch anh HSE) */
  (void)RCC->AHB1ENR;                   /* đọc lại để clock kịp ổn định */

  /* ===== 2. Ngõ ra: PA2 (CS), PA3 (RST), PA4 (DC), PA6 =================== */
  /* Mức ban đầu = 0 (thực hiện TRƯỚC khi chuyển sang output để không bị glitch) */
  GPIOA->ODR &= ~((1UL << 2) | (1UL << 3) | (1UL << 4) | (1UL << 6));

  /* MODER = 01b (Output) */
  GPIOA->MODER   &= ~((0x3UL << (2 * 2)) | (0x3UL << (3 * 2)) | (0x3UL << (4 * 2)) | (0x3UL << (6 * 2)));
  GPIOA->MODER   |=  ((0x1UL << (2 * 2)) | (0x1UL << (3 * 2)) | (0x1UL << (4 * 2)) | (0x1UL << (6 * 2)));

  /* OTYPER = 0 (Push-pull) */
  GPIOA->OTYPER  &= ~((1UL << 2) | (1UL << 3) | (1UL << 4) | (1UL << 6));

  /* OSPEEDR = 00b (Low speed) */
  GPIOA->OSPEEDR &= ~((0x3UL << (2 * 2)) | (0x3UL << (3 * 2)) | (0x3UL << (4 * 2)) | (0x3UL << (6 * 2)));

  /* PUPDR = 00b (No pull) */
  GPIOA->PUPDR   &= ~((0x3UL << (2 * 2)) | (0x3UL << (3 * 2)) | (0x3UL << (4 * 2)) | (0x3UL << (6 * 2)));

  /* ===== 3. Ngõ vào: PC8 (ENC_SW - nút nhấn encoder), pull-up ============ */
  GPIOC->MODER &= ~(0x3UL << (8 * 2));  /* MODER = 00b (Input) */
  GPIOC->PUPDR &= ~(0x3UL << (8 * 2));  /* xóa 2 bit cũ */
  GPIOC->PUPDR |=  (0x1UL << (8 * 2));  /* PUPDR = 01b (Pull-up) */

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* Việc cấu hình PC0..PC5 làm nút nhấn được thực hiện bằng thanh ghi trực tiếp
   * trong hàm Buttons_Init(), gọi ở USER CODE 2 trong main(). */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
