#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include "MAX30101.h"


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

int max30101_write_reg(uint8_t reg, uint8_t value)
{
    return i2c_reg_write_byte_dt(&max30101_i2c, reg, value);
}

int max30101_read_reg(uint8_t reg, uint8_t *value)
{
    return i2c_reg_read_byte_dt(&max30101_i2c, reg, value);
}

int max30101_read_fifo(uint8_t *buf, size_t len)
{
    return i2c_burst_read_dt(&max30101_i2c, MAX30101_REG_FIFO_DATA, buf, len);
}

int max30101_reset_fifo(void)
{
    int err;

    err = max30101_write_reg(MAX30101_REG_FIFO_WR_PTR, 0);
    if (err) {
        return err;
    }
    err = max30101_write_reg(MAX30101_REG_OVF_COUNTER, 0);
    if (err) {
        return err;
    }
    err = max30101_write_reg(MAX30101_REG_FIFO_RD_PTR, 0);
    return err;
}

int max30101_set_led_amplitude(uint8_t red, uint8_t ir, uint8_t green)
{
    int err;

    err = max30101_write_reg(MAX30101_REG_LED1_PA, red);
    if (err) {
        return err;
    }
    err = max30101_write_reg(MAX30101_REG_LED2_PA, ir);
    if (err) {
        return err;
    }
    err = max30101_write_reg(MAX30101_REG_LED3_PA, green);
    return err;
}

