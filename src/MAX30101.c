#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include "MAX30101.h"

#define MAX30101_I2C_ADDR 0x57

#define MAX30101_REG_MODE_CFG    0x09
#define MAX30101_REG_LED1_PA     0x0C
#define MAX30101_REG_LED2_PA     0x0D
#define MAX30101_REG_LED3_PA     0x0E

#define MAX30101_MODE_MULTI_LED  0x07
#define MAX30101_LED_CURRENT_3MA 0x0F

/* Assume sensor is connected to i2c0 */
#define I2C_NODE DT_NODELABEL(i2c0)

static const struct i2c_dt_spec max30101_i2c = I2C_DT_SPEC_GET(I2C_NODE);

int max30101_init(void)
{
    int err;

    if (!device_is_ready(max30101_i2c.bus)) {
        printk("I2C bus not ready\n");
        return -ENODEV;
    }

    err = i2c_reg_write_byte_dt(&max30101_i2c, MAX30101_REG_MODE_CFG, MAX30101_MODE_MULTI_LED);
    if (err) {
        printk("Failed to set mode (err %d)\n", err);
        return err;
    }

    err = i2c_reg_write_byte_dt(&max30101_i2c, MAX30101_REG_LED1_PA, MAX30101_LED_CURRENT_3MA);
    if (err) {
        printk("Failed to set LED1 current (err %d)\n", err);
        return err;
    }

    err = i2c_reg_write_byte_dt(&max30101_i2c, MAX30101_REG_LED2_PA, MAX30101_LED_CURRENT_3MA);
    if (err) {
        printk("Failed to set LED2 current (err %d)\n", err);
        return err;
    }

    err = i2c_reg_write_byte_dt(&max30101_i2c, MAX30101_REG_LED3_PA, MAX30101_LED_CURRENT_3MA);
    if (err) {
        printk("Failed to set LED3 current (err %d)\n", err);
        return err;
    }

    printk("MAX30101 initialized\n");
    return 0;
}

