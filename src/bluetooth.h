#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

int bluetooth_init(void);
void bluetooth_notify(void);
bool bluetooth_was_connected(void);
bool bluetooth_was_disconnected(void);
int bluetooth_restart_adv(void);

#endif /* BLUETOOTH_H_ */
