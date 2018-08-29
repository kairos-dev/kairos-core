#include <stdint.h>
#include <driver/adc.h>
#include <driver/gpio.h>
#include <soc/gpio_struct.h>

#include "keypad.h"

uint8_t keypad_init(void)
{
    return 255;
}

uint8_t keypad_read(void)
{
    return 255;
}