#ifndef SRC_TICKS_H
#define SRC_TICKS_H 1

#include <stdint.h>

void msleep(uint32_t delay);
uint32_t mtime(void);
void systick_setup(int tick_rate);

#endif /* SRC_TICKS_H */

