#ifndef __BMP180_H__
#define __BMP180_H__

#include <driver/i2c.h>
#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"

#define BMP180_ADDRESS 0x77

enum
{
    BMP085_REGISTER_CAL_AC1            = 0xAA,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_AC2            = 0xAC,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_AC3            = 0xAE,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_AC4            = 0xB0,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_AC5            = 0xB2,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_AC6            = 0xB4,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_B1             = 0xB6,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_B2             = 0xB8,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_MB             = 0xBA,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_MC             = 0xBC,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CAL_MD             = 0xBE,  // R   Calibration data (16 bits)
    BMP085_REGISTER_CHIPID             = 0xD0,
    BMP085_REGISTER_VERSION            = 0xD1,
    BMP085_REGISTER_SOFTRESET          = 0xE0,
    BMP085_REGISTER_CONTROL            = 0xF4,
    BMP085_REGISTER_TEMPDATA           = 0xF6,
    BMP085_REGISTER_PRESSUREDATA       = 0xF6,
    BMP085_REGISTER_READTEMPCMD        = 0x2E,
    BMP085_REGISTER_READPRESSURECMD    = 0x34 // 0011 0100
};
typedef enum
{
  BMP085_MODE_ULTRALOWPOWER          = 0,
  BMP085_MODE_STANDARD               = 1,
  BMP085_MODE_HIGHRES                = 2,
  BMP085_MODE_ULTRAHIGHRES           = 3
} bmp085_mode_t;

static char tag[] = "bmp180";

static short readRegister16(uint8_t reg);
static int readRegister24(uint8_t reg);
static uint32_t readUncompensatedTemp();
static uint32_t readUncompensatedPressure(uint32_t mode);
double centigrade_to_fahrenheit(double centigrade);
double pascals_to_inHg(double pressure);
void x();
void task_bmp180(void *ignore);

#endif  // __BMP280_H__