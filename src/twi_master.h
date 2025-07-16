#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

#include <zephyr/device.h>

int twi_master_init(void);
const struct device *twi_master_device_get(void);

#endif /* TWI_MASTER_H_ */
