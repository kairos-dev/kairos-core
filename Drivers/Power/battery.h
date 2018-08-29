#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <stdint.h>
#include <driver/adc.h>
#include "driver/gpio.h"
#include "soc/gpio_struct.h"

#define BATTERY_PIN ADC1_CHANNEL_4 //GPIO_NUM_32

#define MEGA 1000000
#define RESISTOR1 2.7*MEGA
#define RESISTOR2 4.7*MEGA

uint8_t battery_monitor_init(void);

uint16_t get_battery_raw_voltage(void);

uint16_t get_battery_mv(void);

uint8_t get_battery_porcentage(void);

uint16_t _get_battery_value(void);

#endif