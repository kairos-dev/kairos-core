#ifndef _HAL_ACCELEROMETER_H_
#define _HAL_ACCELEROMETER_H_ 

#include <string.h>
#include "def/common.h"
#include "drv/protocols/i2c.h"
#include "drv/accelerometer/bma423.h"

#define ACC_INT_1_GPIO PIN_INT1 
#define ACC_INT_1_MASK (1ULL<<PIN_INT1)
#define ACC_INT_2_GPIO PIN_INT2 
#define ACC_INT_2_MASK (1ULL<<PIN_INT2)

int8_t accelerometer_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void* intf_ptr);
int8_t accelerometer_i2c_read(uint8_t reg_addr,  uint8_t *reg_data, uint32_t length, void* intf_ptr);
void accelerometer_delay_us(uint32_t period_ns, void* intf_ptr);
kairos_err_t init_accelerometer(void);
uint8_t step_count_accelerometer(uint32_t *step_count);
uint8_t get_axis_accelerometer(struct bma4_accel *axis);
uint8_t get_int_status_accelerometer(uint16_t *int_status);

#endif
