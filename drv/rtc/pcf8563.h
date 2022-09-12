
/*
 * Copyright (c) 2020 Ruslan V. Uss <unclerus@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of itscontributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file pcf8563.h
 * @defgroup pcf8563 pcf8563
 * @{
 * This is a modificated verion of the PCF8563 component from esp-idf-lib.
 *
 * ESP-IDF driver for PCF8563 real-time clock/calendar
 *
 * Copyright (c) 2020 Ruslan V. Uss <unclerus@gmail.com>
 *
 * BSD Licensed as described in the file LICENSE
 */
#ifndef _DRV_PCF8563_H_
#define _DRV_PCF8563_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "def/common.h"
#include "drv/protocols/i2c.h"

#define PCF8563_ADDR 0x51

#define I2C_FREQ_HZ 400000

#define REG_CTRL_STATUS1 0x00
#define REG_CTRL_STATUS2 0x01
#define REG_VL_SECONDS   0x02
#define REG_MINUTES      0x03
#define REG_HOURS        0x04
#define REG_DAYS         0x05
#define REG_WEEKDAYS     0x06
#define REG_CENT_MONTHS  0x07
#define REG_YEARS        0x08
#define REG_ALARM_MIN    0x09
#define REG_ALARM_HOUR   0x0a
#define REG_ALARM_DAY    0x0b
#define REG_ALARM_WDAY   0x0c
#define REG_CLKOUT       0x0d
#define REG_TIMER_CTRL   0x0e
#define REG_TIMER        0x0f

#define BIT_YEAR_CENTURY 7
#define BIT_VL 7
#define BIT_AE 7
#define BIT_CLKOUT_FD 0
#define BIT_CLKOUT_FE 7

#define BIT_CTRL_STATUS2_TIE 0
#define BIT_CTRL_STATUS2_AIE 1
#define BIT_CTRL_STATUS2_TF  3
#define BIT_CTRL_STATUS2_AF  4

#define BIT_TIMER_CTRL_TE 7

#define MASK_TIMER_CTRL_TD 0x03
#define MASK_ALARM 0x7f

#define MASK_MIN  0x7f
#define MASK_HOUR 0x3f
#define MASK_MDAY 0x3f
#define MASK_WDAY 0x07
#define MASK_MON  0x1f

#define BV(x) ((uint8_t)(1 << (x)))

/**
 * Frequency output at pin CLKOUT
 */
typedef enum {
    PCF8563_DISABLED = 0, //!< CLKOUT output is inhibited and set high-impedance
    PCF8563_32768HZ,      //!< 32768 Hz
    PCF8563_1024HZ,       //!< 1024 Hz
    PCF8563_32HZ,         //!< 32 Hz
    PCF8563_1HZ,          //!< 1 Hz
} pcf8563_clkout_freq_t;

/**
 * Timer clock
 */
typedef enum {
    PCF8563_TIMER_4096HZ = 0, //!< 4096 Hz
    PCF8563_TIMER_64HZ,       //!< 64 Hz
    PCF8563_TIMER_1HZ,        //!< 1 Hz
    PCF8563_TIMER_1_60HZ      //!< 1/60 Hz
} pcf8563_timer_clock_t;

/**
 * Flags to setup alarm
 */
typedef enum {
    PCF8563_ALARM_MATCH_MIN     = 0x01, //!< Alarm when minute matched
    PCF8563_ALARM_MATCH_HOUR    = 0x02, //!< Alarm when hour matched
    PCF8563_ALARM_MATCH_DAY     = 0x04, //!< Alarm when day matched
    PCF8563_ALARM_MATCH_WEEKDAY = 0x08  //!< Alarm when weekday matched
} pcf8563_alarm_flags_t;

/**
 * @brief Initialize device descriptor
 *
 * @param dev I2C device descriptor
 * @param port I2C port
 * @param sda_gpio SDA GPIO
 * @param scl_gpio SCL GPIO
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_init_desc(i2c_dev_t *dev, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);

/**
 * @brief Free device descriptor
 *
 * @param dev I2C device descriptor
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_free_desc(i2c_dev_t *dev);

/**
 * @brief Set the time on the RTC
 *
 * @param dev I2C device descriptor
 * @param time Pointer to time struct
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_set_time(i2c_dev_t *dev, struct tm *time);

/**
 * @brief Get the time from the RTC
 *
 * @param dev I2C device descriptor
 * @param[out] time Pointer to time struct
 * @param[out] valid Time validity, false when RTC had power failures
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_time(i2c_dev_t *dev, struct tm *time, bool *valid);

/**
 * @brief Set output frequency on CLKOUT pin
 *
 * @param dev I2C device descriptor
 * @param freq Frequency
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_set_clkout(i2c_dev_t *dev, pcf8563_clkout_freq_t freq);

/**
 * @brief Get current frequency on CLKOUT pin
 *
 * @param dev I2C device descriptor
 * @param[out] freq Frequency
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_clkout(i2c_dev_t *dev, pcf8563_clkout_freq_t *freq);

/**
 * @brief Setup timer
 *
 * @param dev I2C device descriptor
 * @param int_enable true for enable interrupt on timer
 * @param clock Timer frequency
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_set_timer_settings(i2c_dev_t *dev, bool int_enable, pcf8563_timer_clock_t clock);

/**
 * @brief Get timer settings
 *
 * @param dev I2C device descriptor
 * @param[out] int_enabled true if timer interrupt is enabled
 * @param[out] clock Timer frequency
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_timer_settings(i2c_dev_t *dev, bool *int_enabled, pcf8563_timer_clock_t *clock);

/**
 * @brief Set timer register value
 *
 * @param dev I2C device descriptor
 * @param value Value to set int timer register
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_set_timer_value(i2c_dev_t *dev, uint8_t value);

/**
 * @brief Get timer register value
 *
 * @param dev I2C device descriptor
 * @param[out] value Timer value
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_timer_value(i2c_dev_t *dev, uint8_t *value);

/**
 * @brief Start timer
 *
 * @param dev I2C device descriptor
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_start_timer(i2c_dev_t *dev);

/**
 * @brief Stop timer
 *
 * @param dev I2C device descriptor
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_stop_timer(i2c_dev_t *dev);

/**
 * @brief Get state of the timer flag
 *
 * @param dev I2C device descriptor
 * @param[out] timer true when flag is set
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_timer_flag(i2c_dev_t *dev, bool *timer);

/**
 * @brief Clear timer flag
 *
 * @param dev I2C device descriptor
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_clear_timer_flag(i2c_dev_t *dev);

/**
 * @brief Setup alarm
 *
 * @param dev I2C device descriptor
 * @param int_enable true to enable alarm interrupt
 * @param flags Alarm types, combination of pcf8563_alarm_flags_t values
 * @param time Alarm time. Only tm_min, tm_hour, tm_mday and tm_wday are used
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_set_alarm(i2c_dev_t *dev, bool int_enable, uint32_t flags, struct tm *time);

/**
 * @brief Get alarm settings
 *
 * @param dev I2C device descriptor
 * @param[out] int_enabled true if alarm interrupt is enabled
 * @param[out] flags Selected alarm types, combination of pcf8563_alarm_flags_t values
 * @param[out] time Alarm time. Only tm_min, tm_hour, tm_mday and tm_wday are used
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_alarm(i2c_dev_t *dev, bool *int_enabled, uint32_t *flags, struct tm *time);

/**
 * @brief Get alarm flag
 *
 * @param dev I2C device descriptor
 * @param[out] alarm true if alarm occurred
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_get_alarm_flag(i2c_dev_t *dev, bool *alarm);

/**
 * @brief Clear alarm flag
 *
 * @param dev I2C device descriptor
 * @return `KAIROS_ERR_OK` on success
 */
kairos_err_t pcf8563_clear_alarm_flag(i2c_dev_t *dev);

#endif
