/**
 * @file lv_conf.h
 * Configuration file for v9.2.3-dev
 *
 * ĐÃ RÚT GỌN để giảm dung lượng flash (dự án chỉ hiển thị ảnh). Các dòng đã đổi giá trị
 * được đánh dấu "[OFF]" hoặc "[CHANGED]". Những chỗ tắt gồm:
 *   - Font: bỏ Montserrat 14, dùng font UNSCII 8 rất nhỏ làm font mặc định
 *   - Toàn bộ widget không dùng (giữ lại LV_USE_IMAGE và LV_USE_LABEL)
 *   - Theme Simple / Mono, layout Flex / Grid, observer
 *   - Renderer "complex" (bo góc, đổ bóng, cung tròn) của draw SW
 *
 * LƯU Ý: KHÔNG comment dòng #define để tắt. Với lv_conf_internal.h, thiếu #define thì
 * widget sẽ lấy giá trị mặc định = 1 (BẬT lại). Muốn tắt phải để giá trị = 0.
 */

/* clang-format off */
#if 1 /*Set it to "1" to enable content*/

#ifndef LV_CONF_H
#define LV_CONF_H

/*If you need to include anything here, do it inside the `__ASSEMBLY__` guard */
#if  0 && defined(__ASSEMBLY__)
#include "my_include.h"
#endif

/*====================
   COLOR SETTINGS
 *====================*/

/*Color depth: 1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888)*/
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/

#define LV_USE_STDLIB_MALLOC    LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_STRING    LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_BUILTIN

#define LV_STDINT_INCLUDE       <stdint.h>
#define LV_STDDEF_INCLUDE       <stddef.h>
#define LV_STDBOOL_INCLUDE      <stdbool.h>
#define LV_INTTYPES_INCLUDE     <inttypes.h>
#define LV_LIMITS_INCLUDE       <limits.h>
#define LV_STDARG_INCLUDE       <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    /*Size of the memory available for `lv_malloc()` in bytes (>= 2kB)*/
    #define LV_MEM_SIZE (32 * 1024U)          /*[bytes]*/

    /*Size of the memory expand for `lv_malloc()` in bytes*/
    #define LV_MEM_POOL_EXPAND_SIZE 0

    /*Set an address for the memory pool instead of allocating it as a normal array. Can be in external SRAM too.*/
    #define LV_MEM_ADR 0     /*0: unused*/
    /*Instead of an address give a memory allocator that will be called to get a memory pool for LVGL. E.g. my_malloc*/
    #if LV_MEM_ADR == 0
        #undef LV_MEM_POOL_INCLUDE
        #undef LV_MEM_POOL_ALLOC
    #endif
#endif  /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
   HAL SETTINGS
 *====================*/

/*Default display refresh, input device read and animation step period.*/
#define LV_DEF_REFR_PERIOD  33      /*[ms]*/

/*Default Dot Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 *(Not so important, you can adjust it to modify default sizes and spaces)*/
#define LV_DPI_DEF 130     /*[px/inch]*/

/*=================
 * OPERATING SYSTEM
 *=================*/
#define LV_USE_OS   LV_OS_NONE

#if LV_USE_OS == LV_OS_CUSTOM
    #define LV_OS_CUSTOM_INCLUDE <stdint.h>
#endif
#if LV_USE_OS == LV_OS_FREERTOS
	#define LV_USE_FREERTOS_TASK_NOTIFY 1
#endif

/*========================
 * RENDERING CONFIGURATION
 *========================*/

/*Align the stride of all layers and images to this bytes*/
#define LV_DRAW_BUF_STRIDE_ALIGN                1

/*Align the start address of draw_buf addresses to this bytes*/
#define LV_DRAW_BUF_ALIGN                       4

/*Using matrix for transformations.
 *Requirements:
    `LV_USE_MATRIX = 1`.
    The rendering engine needs to support 3x3 matrix transformations.*/
#define LV_DRAW_TRANSFORM_USE_MATRIX            0

/*The target buffer size for simple layer chunks.*/
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE    (24 * 1024)   /*[bytes]*/

/* The stack size of the drawing thread.
 * NOTE: If FreeType or ThorVG is enabled, it is recommended to set it to 32KB or more.
 */
#define LV_DRAW_THREAD_STACK_SIZE    (8 * 1024)   /*[bytes]*/

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW == 1

	/*
	 * Selectively disable color format support in order to reduce code size.
	 * NOTE: some features use certain color formats internally, e.g.
	 * - gradients use RGB888
	 * - bitmaps with transparency may use ARGB8888
	 */

	#define LV_DRAW_SW_SUPPORT_RGB565		1
	#define LV_DRAW_SW_SUPPORT_RGB565A8		1
	#define LV_DRAW_SW_SUPPORT_RGB888		1
	#define LV_DRAW_SW_SUPPORT_XRGB8888		1
	#define LV_DRAW_SW_SUPPORT_ARGB8888		1
	#define LV_DRAW_SW_SUPPORT_L8			1
	#define LV_DRAW_SW_SUPPORT_AL88			1
	#define LV_DRAW_SW_SUPPORT_A8			1
	#define LV_DRAW_SW_SUPPORT_I1			1

	/* Set the number of draw unit.
     * > 1 requires an operating system enabled in `LV_USE_OS`
     * > 1 means multiple threads will render the screen in parallel */
    #define LV_DRAW_SW_DRAW_UNIT_CNT    1

    /* Use Arm-2D to accelerate the sw render */
    #define LV_USE_DRAW_ARM2D_SYNC      0

    /* Enable native helium assembly to be compiled */
    #define LV_USE_NATIVE_HELIUM_ASM    0

    /* 0: use a simple renderer capable of drawing only simple rectangles with gradient, images, texts, and straight lines only
     * 1: use a complex renderer capable of drawing rounded corners, shadow, skew lines, and arcs too */
    #define LV_DRAW_SW_COMPLEX          0   /* [OFF] chỉ hiển thị ảnh + nền phẳng, không cần bo góc/đổ bóng/cung tròn */

    #if LV_DRAW_SW_COMPLEX == 1
        #define LV_DRAW_SW_SHADOW_CACHE_SIZE 0
        #define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
    #endif

    #define  LV_USE_DRAW_SW_ASM     LV_DRAW_SW_ASM_NONE

    #if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
        #define  LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
    #endif

    /* Enable drawing complex gradients in software: linear at an angle, radial or conical */
    #define LV_USE_DRAW_SW_COMPLEX_GRADIENTS    0
#endif

/* Use NXP's VG-Lite GPU on iMX RTxxx platforms. */
#define LV_USE_DRAW_VGLITE 0

/* Use NXP's PXP on iMX RTxxx platforms. */
#define LV_USE_PXP 0

/* Use Renesas Dave2D on RA  platforms. */
#define LV_USE_DRAW_DAVE2D 0

/* Draw using cached SDL textures*/
#define LV_USE_DRAW_SDL 0

/* Use VG-Lite GPU. */
#define LV_USE_DRAW_VG_LITE 0

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*-------------
 * Logging
 *-----------*/

/*Enable the log module*/
#define LV_USE_LOG 0

/*-------------
 * Asserts
 *-----------*/

/*Enable asserts if an operation is failed or an invalid data is found.
 *If LV_USE_LOG is enabled an error message will be printed on failure*/
#define LV_USE_ASSERT_NULL          1   /*Check if the parameter is NULL. (Very fast, recommended)*/
#define LV_USE_ASSERT_MALLOC        1   /*Checks is the memory is successfully allocated or no. (Very fast, recommended)*/
#define LV_USE_ASSERT_STYLE         0   /*Check if the styles are properly initialized. (Very fast, recommended)*/
#define LV_USE_ASSERT_MEM_INTEGRITY 0   /*Check the integrity of `lv_mem` after critical operations. (Slow)*/
#define LV_USE_ASSERT_OBJ           0   /*Check the object's type and existence (e.g. not deleted). (Slow)*/

/*Add a custom handler when assert happens e.g. to restart the MCU*/
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while(1);   /*Halt by default*/

/*-------------
 * Debug
 *-----------*/

/*1: Draw random colored rectangles over the redrawn areas*/
#define LV_USE_REFR_DEBUG 0

/*1: Draw a red overlay for ARGB layers and a green overlay for RGB layers*/
#define LV_USE_LAYER_DEBUG 0

/*1: Draw overlays with different colors for each draw_unit's tasks.*/
#define LV_USE_PARALLEL_DRAW_DEBUG 0

/*-------------
 * Others
 *-----------*/

#define LV_ENABLE_GLOBAL_CUSTOM 0
#if LV_ENABLE_GLOBAL_CUSTOM
    /*Header to include for the custom 'lv_global' function"*/
    #define LV_GLOBAL_CUSTOM_INCLUDE <stdint.h>
#endif

/*Default cache size in bytes.*/
#define LV_CACHE_DEF_SIZE       0

/*Default number of image header cache entries.*/
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 0

/*Number of stops allowed per gradient. Increase this to allow more stops.
 *This adds (sizeof(lv_color_t) + 1) bytes per additional stop*/
#define LV_GRADIENT_MAX_STOPS   2

/* Adjust color mix functions rounding. */
#define LV_COLOR_MIX_ROUND_OFS  0

/* Add 2 x 32 bit variables to each lv_obj_t to speed up getting style properties */
#define LV_OBJ_STYLE_CACHE      0

/* Add `id` field to `lv_obj_t` */
#define LV_USE_OBJ_ID           0

/* Automatically assign an ID when obj is created */
#define LV_OBJ_ID_AUTO_ASSIGN   LV_USE_OBJ_ID

/*Use the builtin obj ID handler functions*/
#define LV_USE_OBJ_ID_BUILTIN   1

/*Use obj property set/get API*/
#define LV_USE_OBJ_PROPERTY 0

/*Enable property name support*/
#define LV_USE_OBJ_PROPERTY_NAME 1

/* VG-Lite Simulator */
#define LV_USE_VG_LITE_THORVG  0

/*=====================
 *  COMPILER SETTINGS
 *====================*/

/*For big endian systems set to 1*/
#define LV_BIG_ENDIAN_SYSTEM 0

/*Define a custom attribute to `lv_tick_inc` function*/
#define LV_ATTRIBUTE_TICK_INC

/*Define a custom attribute to `lv_timer_handler` function*/
#define LV_ATTRIBUTE_TIMER_HANDLER

/*Define a custom attribute to `lv_display_flush_ready` function*/
#define LV_ATTRIBUTE_FLUSH_READY

/*Required alignment size for buffers*/
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1

/*Will be added where memories needs to be aligned (with -Os data might not be aligned to boundary by default).
 * E.g. __attribute__((aligned(4)))*/
#define LV_ATTRIBUTE_MEM_ALIGN

/*Attribute to mark large constant arrays for example font's bitmaps*/
#define LV_ATTRIBUTE_LARGE_CONST

/*Compiler prefix for a big array declaration in RAM*/
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY

/*Place performance critical functions into a faster memory (e.g RAM)*/
#define LV_ATTRIBUTE_FAST_MEM

/*Export integer constant to binding.*/
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning /*The default value just prevents GCC warning*/

/*Prefix all global extern data with this*/
#define LV_ATTRIBUTE_EXTERN_DATA

/* Use `float` as `lv_value_precise_t` */
#define LV_USE_FLOAT            0

/*Enable matrix support
 *Requires `LV_USE_FLOAT = 1`*/
#define LV_USE_MATRIX           0

/*Include `lvgl_private.h` in `lvgl.h` to access internal data and functions by default*/
#define LV_USE_PRIVATE_API		0

/*==================
 *   FONT USAGE
 *===================*/

/*Montserrat fonts with ASCII range and some symbols using bpp = 4*/
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 0   /* [OFF] */
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/*Demonstrate special features*/
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0  /*bpp = 3*/
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0  /*Hebrew, Arabic, Persian letters and all their forms*/
#define LV_FONT_SIMSUN_14_CJK            0  /*1000 most common CJK radicals*/
#define LV_FONT_SIMSUN_16_CJK            0  /*1000 most common CJK radicals*/

/*Pixel perfect monospace fonts*/
#define LV_FONT_UNSCII_8  1   /* [CHANGED] LVGL bắt buộc phải có 1 font mặc định; font này chỉ nặng vài KB */
#define LV_FONT_UNSCII_16 0

/*Optionally declare custom fonts here.*/
#define LV_FONT_CUSTOM_DECLARE

/*Always set a default font*/
#define LV_FONT_DEFAULT &lv_font_unscii_8   /* [CHANGED] trước là &lv_font_montserrat_14 */

/*Enable handling large font and/or fonts with a lot of characters.*/
#define LV_FONT_FMT_TXT_LARGE 0

/*Enables/disables support for compressed fonts.*/
#define LV_USE_FONT_COMPRESSED 0

/*Enable drawing placeholders when glyph dsc is not found*/
#define LV_USE_FONT_PLACEHOLDER 1

/*=================
 *  TEXT SETTINGS
 *=================*/

#define LV_TXT_ENC LV_TXT_ENC_UTF8

/*Can break (wrap) texts on these chars*/
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

#define LV_TXT_LINE_BREAK_LONG_LEN 0
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/*Support bidirectional texts.*/
#define LV_USE_BIDI 0
#if LV_USE_BIDI
    #define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

/*Enable Arabic/Persian processing*/
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*==================
 * WIDGETS
 *================*/

#define LV_WIDGETS_HAS_DEFAULT_VALUE  1

#define LV_USE_ANIMIMG    0   /* [OFF] */

#define LV_USE_ARC        0   /* [OFF] */

#define LV_USE_BAR        0   /* [OFF] */

#define LV_USE_BUTTON        0   /* [OFF] */

#define LV_USE_BUTTONMATRIX  0   /* [OFF] */

#define LV_USE_CALENDAR   0   /* [OFF] */
#if LV_USE_CALENDAR
    #define LV_CALENDAR_WEEK_STARTS_MONDAY 0
    #if LV_CALENDAR_WEEK_STARTS_MONDAY
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}
    #else
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}
    #endif

    #define LV_CALENDAR_DEFAULT_MONTH_NAMES {"January", "February", "March",  "April", "May",  "June", "July", "August", "September", "October", "November", "December"}
    #define LV_USE_CALENDAR_HEADER_ARROW 1
    #define LV_USE_CALENDAR_HEADER_DROPDOWN 1
    #define LV_USE_CALENDAR_CHINESE 0
#endif  /*LV_USE_CALENDAR*/

#define LV_USE_CANVAS     0   /* [OFF] */

#define LV_USE_CHART      0   /* [OFF] */

#define LV_USE_CHECKBOX   0   /* [OFF] */

#define LV_USE_DROPDOWN   0   /* [OFF] */

#define LV_USE_IMAGE      1   /*Requires: lv_label  -- GIỮ LẠI, đang dùng để hiện ảnh*/

#define LV_USE_IMAGEBUTTON     0   /* [OFF] */

#define LV_USE_KEYBOARD   0   /* [OFF] */

#define LV_USE_LABEL      1   /* GIỮ LẠI vì LV_USE_IMAGE cần */
#if LV_USE_LABEL
    #define LV_LABEL_TEXT_SELECTION 0 /* [OFF] */
    #define LV_LABEL_LONG_TXT_HINT 1  /*Store some extra info in labels to speed up drawing of very long texts*/
    #define LV_LABEL_WAIT_CHAR_COUNT 3  /*The count of wait chart*/
#endif

#define LV_USE_LED        0   /* [OFF] */

#define LV_USE_LINE       0   /* [OFF] */

#define LV_USE_LIST       0   /* [OFF] */

#define LV_USE_LOTTIE     0  /*Requires: lv_canvas, thorvg */

#define LV_USE_MENU       0   /* [OFF] */

#define LV_USE_MSGBOX     0   /* [OFF] */

#define LV_USE_ROLLER     0   /* [OFF] */

#define LV_USE_SCALE      0   /* [OFF] */

#define LV_USE_SLIDER     0   /* [OFF] */

#define LV_USE_SPAN       0   /* [OFF] */
#if LV_USE_SPAN
    #define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif

#define LV_USE_SPINBOX    0   /* [OFF] */

#define LV_USE_SPINNER    0   /* [OFF] */

#define LV_USE_SWITCH     0   /* [OFF] */

#define LV_USE_TEXTAREA   0   /* [OFF] */
#if LV_USE_TEXTAREA != 0
    #define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500    /*ms*/
#endif

#define LV_USE_TABLE      0   /* [OFF] */

#define LV_USE_TABVIEW    0   /* [OFF] */

#define LV_USE_TILEVIEW   0   /* [OFF] */

#define LV_USE_WIN        0   /* [OFF] */

/*==================
 * THEMES
 *==================*/

/*A simple, impressive and very complete theme*/
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT

    /*0: Light mode; 1: Dark mode*/
    #define LV_THEME_DEFAULT_DARK 0

    /*1: Enable grow on press*/
    #define LV_THEME_DEFAULT_GROW 0   /* [OFF] chỉ dành cho nút bấm */

    /*Default transition time in [ms]*/
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/*A very simple theme that is a good starting point for a custom theme*/
#define LV_USE_THEME_SIMPLE 0   /* [OFF] */

/*A theme designed for monochrome displays*/
#define LV_USE_THEME_MONO 0   /* [OFF] */

/*==================
 * LAYOUTS
 *==================*/

/*A layout similar to Flexbox in CSS.*/
#define LV_USE_FLEX 0   /* [OFF] */

/*A layout similar to Grid in CSS.*/
#define LV_USE_GRID 0   /* [OFF] */

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/

/*Setting a default driver letter allows skipping the driver prefix in filepaths*/
#define LV_FS_DEFAULT_DRIVE_LETTER '\0'

#define LV_USE_FS_STDIO 0
#define LV_USE_FS_POSIX 0
#define LV_USE_FS_WIN32 0
#define LV_USE_FS_FATFS 0
#define LV_USE_FS_MEMFS 0
#define LV_USE_FS_LITTLEFS 0
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
#define LV_USE_FS_ARDUINO_SD 0

/*LODEPNG decoder library*/
#define LV_USE_LODEPNG 0

/*PNG decoder(libpng) library*/
#define LV_USE_LIBPNG 0

/*BMP decoder library*/
#define LV_USE_BMP 0

/* JPG + split JPG decoder library. */
#define LV_USE_TJPGD 0

/* libjpeg-turbo decoder library. */
#define LV_USE_LIBJPEG_TURBO 0

/*GIF decoder library*/
#define LV_USE_GIF 0
#if LV_USE_GIF
    #define LV_GIF_CACHE_DECODE_DATA 0
#endif

/*Decode bin images to RAM*/
#define LV_BIN_DECODER_RAM_LOAD 0

/*RLE decompress library*/
#define LV_USE_RLE 0

/*QR code library*/
#define LV_USE_QRCODE 0

/*Barcode code library*/
#define LV_USE_BARCODE 0

/*FreeType library*/
#define LV_USE_FREETYPE 0

/* Built-in TTF decoder */
#define LV_USE_TINY_TTF 0

/*Rlottie library*/
#define LV_USE_RLOTTIE 0

/*Enable Vector Graphic APIs
 *Requires `LV_USE_MATRIX = 1`*/
#define LV_USE_VECTOR_GRAPHIC  0

/* Enable ThorVG (vector graphics library) from the src/libs folder */
#define LV_USE_THORVG_INTERNAL 0

/* Enable ThorVG by assuming that its installed and linked to the project */
#define LV_USE_THORVG_EXTERNAL 0

/*Use lvgl built-in LZ4 lib*/
#define LV_USE_LZ4_INTERNAL  0

/*Use external LZ4 library*/
#define LV_USE_LZ4_EXTERNAL  0

/*FFmpeg library for image decoding and playing videos*/
#define LV_USE_FFMPEG 0

/*==================
 * OTHERS
 *==================*/

/*1: Enable API to take snapshot for object*/
#define LV_USE_SNAPSHOT 0

/*1: Enable system monitor component*/
#define LV_USE_SYSMON   0

/*1: Enable the runtime performance profiler*/
#define LV_USE_PROFILER 0

/*1: Enable Monkey test*/
#define LV_USE_MONKEY 0

/*1: Enable grid navigation*/
#define LV_USE_GRIDNAV 0

/*1: Enable lv_obj fragment*/
#define LV_USE_FRAGMENT 0

/*1: Support using images as font in label or span widgets */
#define LV_USE_IMGFONT 0

/*1: Enable an observer pattern implementation*/
#define LV_USE_OBSERVER 0   /* [OFF] */

/*1: Enable Pinyin input method*/
#define LV_USE_IME_PINYIN 0

/*1: Enable file explorer*/
#define LV_USE_FILE_EXPLORER                     0

/*==================
 * DEVICES
 *==================*/

#define LV_USE_SDL              0
#define LV_USE_X11              0
#define LV_USE_WAYLAND          0
#define LV_USE_LINUX_FBDEV      0
#define LV_USE_NUTTX            0
#define LV_USE_LINUX_DRM        0
#define LV_USE_TFT_ESPI         0
#define LV_USE_EVDEV            0
#define LV_USE_LIBINPUT         0

/*Drivers for LCD devices connected via SPI/parallel port*/
#define LV_USE_ST7735        0
#define LV_USE_ST7789        1
#define LV_USE_ST7796        0
#define LV_USE_ILI9341       0

#define LV_USE_GENERIC_MIPI (LV_USE_ST7735 | LV_USE_ST7789 | LV_USE_ST7796 | LV_USE_ILI9341)

/*Driver for Renesas GLCD*/
#define LV_USE_RENESAS_GLCDC    0

/* LVGL Windows backend */
#define LV_USE_WINDOWS    0

/* Use OpenGL to open window on PC and handle mouse and keyboard */
#define LV_USE_OPENGLES   0

/* QNX Screen display and input drivers */
#define LV_USE_QNX              0

/*==================
* EXAMPLES
*==================*/

/*Enable the examples to be built with the library*/
#define LV_BUILD_EXAMPLES 0

/*===================
 * DEMO USAGE
 ====================*/

#define LV_USE_DEMO_WIDGETS 0
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0
#define LV_USE_DEMO_BENCHMARK 0
#define LV_USE_DEMO_RENDER 0
#define LV_USE_DEMO_STRESS 0
#define LV_USE_DEMO_MUSIC 0
#define LV_USE_DEMO_FLEX_LAYOUT     0
#define LV_USE_DEMO_MULTILANG       0
#define LV_USE_DEMO_TRANSFORM       0
#define LV_USE_DEMO_SCROLL          0
#define LV_USE_DEMO_VECTOR_GRAPHIC  0

/*--END OF LV_CONF_H--*/

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/
