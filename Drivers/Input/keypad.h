#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <stdint.h>

uint8_t keypad_init(void);

uint8_t keypad_read(void);

#endif