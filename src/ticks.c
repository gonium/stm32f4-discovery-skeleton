#include "ticks.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

volatile uint32_t system_millis;

/* Called when systick fires */
void sys_tick_handler(void) {
    system_millis++;
}

/* sleep for delay milliseconds */
void msleep(uint32_t delay) {
    uint32_t wake = system_millis + delay;
    while (wake > system_millis) ;
}

/* return the time */
uint32_t mtime() {
    return system_millis;
}

/* Set up a timer to create 1mS ticks. */
void systick_setup(int tick_rate) {
    /* clock rate / 1000 to get 1mS interrupt rate */
    systick_set_reload((168000000) / tick_rate);
    STK_CSR = 0x07;
}
