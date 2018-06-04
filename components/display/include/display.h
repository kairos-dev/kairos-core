#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <u8g2_esp32_hal.h>
#include <app.h>
#include <top_menu_icons.h>
#include <app_icons.h>


u8g2_t display_setup(void);

void display_battery(u8g2_t u8g2, const uint8_t *bitmap);

void display_bluetooth(u8g2_t u8g2, const uint8_t *bitmap);

void display_icon(u8g2_t u8g2, const icon_t bitmap);

void display_text(u8g2_t u8g2, const char *text);

void display_animate_left_arrow(u8g2_t u8g2, const uint8_t *battery, const uint8_t *bluetooth, const app_t app);

void display_animate_right_arrow(u8g2_t u8g2, const uint8_t *battery, const uint8_t *bluetooth, const app_t app);

void display_screen(u8g2_t u8g2, const uint8_t *battery, const uint8_t *bluetooth, const app_t app);

#endif