#ifndef LCD_PORT_H
#define LCD_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Reset the panel, init LVGL and create the ST7789 display. */
void lcd_init(void);

#ifdef __cplusplus
}
#endif

#endif /* LCD_PORT_H */
