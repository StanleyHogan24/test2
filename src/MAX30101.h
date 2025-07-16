#ifndef MAX30101_H_
#define MAX30101_H_

#include <zephyr/sys/util.h>

/* I2C address */
#define MAX30101_I2C_ADDR         0x57

/* Register addresses */
#define MAX30101_REG_INTR_STATUS_1    0x00
#define MAX30101_REG_INTR_STATUS_2    0x01
#define MAX30101_REG_INTR_ENABLE_1    0x02
#define MAX30101_REG_INTR_ENABLE_2    0x03
#define MAX30101_REG_FIFO_WR_PTR      0x04
#define MAX30101_REG_OVF_COUNTER      0x05
#define MAX30101_REG_FIFO_RD_PTR      0x06
#define MAX30101_REG_FIFO_DATA        0x07
#define MAX30101_REG_FIFO_CFG         0x08
#define MAX30101_REG_MODE_CFG         0x09
#define MAX30101_REG_SPO2_CFG         0x0A
#define MAX30101_REG_LED1_PA          0x0C
#define MAX30101_REG_LED2_PA          0x0D
#define MAX30101_REG_LED3_PA          0x0E
#define MAX30101_REG_MULTI_LED_CTRL1  0x11
#define MAX30101_REG_MULTI_LED_CTRL2  0x12

/* Useful values */
#define MAX30101_MODE_MULTI_LED   0x07
#define MAX30101_LED_CURRENT_3MA  0x0F

int max30101_init(void);
int max30101_write_reg(uint8_t reg, uint8_t value);
int max30101_read_reg(uint8_t reg, uint8_t *value);
int max30101_read_fifo(uint8_t *buf, size_t len);
int max30101_reset_fifo(void);
int max30101_set_led_amplitude(uint8_t red, uint8_t ir, uint8_t green);

#endif /* MAX30101_H_ */
