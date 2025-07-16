#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

#define TWI_NODE DT_NODELABEL(i2c0)

static const struct device *const twi_dev = DEVICE_DT_GET(TWI_NODE);

int twi_master_init(void)
{
    if (!device_is_ready(twi_dev)) {
        printk("TWI master device not ready\n");
        return -ENODEV;
    }

    return 0;
}

const struct device *twi_master_device_get(void)
{
    return twi_dev;
}
