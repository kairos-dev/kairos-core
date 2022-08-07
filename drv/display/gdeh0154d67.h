#ifndef GDEH0154D67_H
#define GDEH0154D67_H

#include <driver/gpio.h>
#include <rom/gpio.h>
#include "def/common.h"

/**************
 * MACROS
 *************/
#define EPD_W21_MOSI_0  gpio_set_level(PIN_MOSI, 0)
#define EPD_W21_MOSI_1  gpio_set_level(PIN_MOSI, 1)

#define EPD_W21_CLK_0 gpio_set_level(PIN_SCLK, 0)
#define EPD_W21_CLK_1 gpio_set_level(PIN_SCLK, 1)

#define EPD_W21_CS_0 gpio_set_level(PIN_CS, 0)
#define EPD_W21_CS_1 gpio_set_level(PIN_CS, 1)

#define EPD_W21_DC_0  gpio_set_level(PIN_DC, 0)
#define EPD_W21_DC_1  gpio_set_level(PIN_DC, 1)
#define EPD_W21_RST_0 gpio_set_level(PIN_RES, 0)
#define EPD_W21_RST_1 gpio_set_level(PIN_RES, 1)
#define isEPD_W21_BUSY gpio_get_level(PIN_BUSY)

#define MONOMSB_MODE 1
#define MONOLSB_MODE 2
#define RED_MODE     3

#define MAX_LINE_BYTES 25// =200/8
#define MAX_COLUMN_BYTES  200

#define ALLSCREEN_GRAGHBYTES 5000

#define pgm_read_byte(addr)   (*(const unsigned char *)(addr))
/**********************
* Functions Prototypes
***********************/

void driver_delay_us(unsigned int xus);
void driver_delay_xms(unsigned long xms);
void DELAY_S(unsigned int delaytime);
void SPI_Delay(unsigned char xrate);
void SPI_Write(unsigned char value);
void Epaper_Write_Command(unsigned char command);
void Epaper_Write_Data(unsigned char command);

//EPD
void Epaper_READBUSY(void);
void SPI_Write(unsigned char TxData);
void Epaper_Write_Command(unsigned char cmd);
void Epaper_Write_Data(unsigned char datas);

void EPD_HW_Init(void); //Electronic paper initialization
void EPD_Part_Init(void); //Local refresh initialization

void EPD_Part_Update(void);
void EPD_Update(void);

void EPD_WhiteScreen_Black(void);
void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void);

//Display
void EPD_WhiteScreen_ALL(const unsigned char * datas);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);

kairos_err_t init_gdeh0154d67(void);

#endif
