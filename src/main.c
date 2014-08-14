/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#define USART_CONSOLE USART2

int _write(int file, char *ptr, int len);

static void clock_setup(void) {
	/* Enable GPIOD clock for LED & USARTs. */
	rcc_periph_clock_enable(RCC_GPIOD);
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Enable clocks for USART2. */
	rcc_periph_clock_enable(RCC_USART2);
}

static void usart_setup(void) {
	/* Setup USART2 parameters. */
	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	/* Finally enable the USART. */
	usart_enable(USART2);
}

static void gpio_setup(void) {
	/* Setup GPIO pin GPIO12 on GPIO port D for LED. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

	/* Setup GPIO pins for USART2 transmit. */
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);

	/* Setup USART2 TX pin as alternate function. */
	gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

/**
 * Use USART_CONSOLE as a console.
 * This is a syscall for newlib
 * @param file
 * @param ptr
 * @param len
 * @return
 */
int _write(int file, char *ptr, int len) {
  int i;

  if (file == STDOUT_FILENO || file == STDERR_FILENO) {
	for (i = 0; i < len; i++) {
	  if (ptr[i] == '\n') {
		usart_send_blocking(USART_CONSOLE, '\r');
	  }
	  usart_send_blocking(USART_CONSOLE, ptr[i]);
	}
	return i;
  }
  errno = EIO;
  return -1;
}

int main(void) {
  int i, j = 0, c = 0;

  clock_setup();
  gpio_setup();
  usart_setup();

  printf("\r\nSTM32F4-Discovery skeleton code started.\r\n");
  while (1) {
	/* Blink the LED (PD12) on the board with every transmitted byte. */
	gpio_toggle(GPIOD, GPIO12);	/* LED on/off */
	printf("%d", c);
	fflush(stdout);
	//usart_send_blocking(USART2, c + '0'); /* USART2: Send byte. */
	c = (c == 9) ? 0 : c + 1;	/* Increment c. */
	if ((j++ % 80) == 0) {		/* Newline after line full. */
	  usart_send_blocking(USART2, '\r');
	  usart_send_blocking(USART2, '\n');
	}
	for (i = 0; i < 3000000; i++) {	/* Wait a bit. */
	  __asm__("NOP");
	}
  }
  return 0;
}
