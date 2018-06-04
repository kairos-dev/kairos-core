#include <string.h>
#include <display.h>
#include <u8g2_esp32_hal.h>
#include <app.h>

u8g2_t display_setup(void){
  u8g2_t u8g2;
  u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
  u8g2_esp32_hal.sda = PIN_SDA;
  u8g2_esp32_hal.scl = PIN_SCL;
  u8g2_esp32_hal_init(u8g2_esp32_hal);

  u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8g2_esp32_msg_i2c_cb, u8g2_esp32_msg_i2c_and_delay_cb);

  u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);   // set the display address
  u8g2_InitDisplay(&u8g2);                // initialize the display
  u8g2_SetPowerSave(&u8g2, 0);            // wake up the display
  return u8g2;
}

void display_battery(u8g2_t u8g2, const uint8_t *bitmap)
{
	u8g2_DrawXBMP(&u8g2, 128-24, 0, 24, 16, bitmap);
	// u8g2_SendBuffer(&u8g2);
}

void display_bluetooth(u8g2_t u8g2, const uint8_t *bitmap)
{
	u8g2_DrawXBMP(&u8g2, 128-48, 0, 24, 16, bitmap);
	// u8g2_SendBuffer(&u8g2);
}

void display_icon(u8g2_t u8g2, const icon_t bitmap)
{
	u8g2_DrawXBM(&u8g2, 12, 28, left_arrow_icon.widht, left_arrow_icon.heidht, left_arrow_icon.image);
	u8g2_DrawXBMP(&u8g2, 46, 16, bitmap.widht, bitmap.heidht, bitmap.image);
	u8g2_DrawXBM(&u8g2, 128-36, 28, right_arrow_icon.widht, right_arrow_icon.heidht, right_arrow_icon.image);
	// u8g2_SendBuffer(&u8g2);	
}

void display_text(u8g2_t u8g2, const char *text)
{
	u8g2_SetFont(&u8g2, u8g2_font_timR08_tf);
	u8g2_DrawStr(&u8g2, 64-(2.3*strlen(text)), 64 ,text);
	// u8g2_DrawStr(&u8g2, 64-(5.5*strlen(text)), 64, text);
}

void display_animate_left_arrow(u8g2_t u8g2, const uint8_t *battery, const uint8_t *bluetooth, const app_t app)
{	u8g2_ClearBuffer(&u8g2);
	display_battery(u8g2, battery);
	display_bluetooth(u8g2, bluetooth);
	u8g2_DrawXBMP(&u8g2, 46, 16, app.icon.widht, app.icon.heidht, app.icon.image);
	u8g2_DrawXBM(&u8g2, 128-36, 28, right_arrow_icon.widht, right_arrow_icon.heidht, right_arrow_icon.image);
	display_text(u8g2, app.info.name);
	u8g2_SendBuffer(&u8g2);
	for(unsigned int index = 0; index < 6 ; index++)
	{
		u8g2_DrawXBM(&u8g2, 12-(4*index), 28, left_arrow_icon.widht, left_arrow_icon.heidht, left_arrow_icon.image);
		u8g2_SendBuffer(&u8g2);
	}
}

void display_animate_right_arrow(u8g2_t u8g2, const uint8_t *battery, const uint8_t *bluetooth, const app_t app)
{	
	// u8g2_SendBuffer(&u8g2);
	for(unsigned int index = 0; index < 6 ; index++)
	{u8g2_ClearBuffer(&u8g2);
	display_battery(u8g2, battery);
	display_bluetooth(u8g2, bluetooth);
	u8g2_DrawXBM(&u8g2, 12, 28, left_arrow_icon.widht, left_arrow_icon.heidht, left_arrow_icon.image);
	u8g2_DrawXBMP(&u8g2, 46, 16, app.icon.widht, app.icon.heidht, app.icon.image);
	// u8g2_DrawXBM(&u8g2, 128-36, 28, right_arrow_icon.widht, right_arrow_icon.heidht, right_arrow_icon.image);
	display_text(u8g2, app.info.name);
		u8g2_DrawXBM(&u8g2, (128-36)+(4*index), 28, right_arrow_icon.widht, right_arrow_icon.heidht, right_arrow_icon.image);
		u8g2_SendBuffer(&u8g2);
	}
}

void display_screen(u8g2_t u8g2, const uint8_t *battery, const uint8_t *bluetooth, const app_t app)
{
	u8g2_ClearBuffer(&u8g2);
	display_battery(u8g2, battery);
	display_bluetooth(u8g2, bluetooth);
	display_icon(u8g2, app.icon);
	display_text(u8g2, app.info.name);
	u8g2_SendBuffer(&u8g2);
}