Project template for STM32F4-Discovery Boards
=============================================

This is a simple bare-metal project template for the STM32F4 Discovery board.
It is based on:

* [libopencm3 example code](https://github.com/libopencm3/libopencm3-examples)

Prerequisites
-------------

* Install [gcc-arm-embedded](https://launchpad.net/gcc-arm-embedded) and
  make sure the arm-none-eabi-*-commands are in your path
* Install [OpenOCD](http://openocd.sourceforge.net/)

Usage
-----

First, you need to grab and compile a copy of libopencm3:

	$ git submodule init
	$ git submodule update
	$ cd libopencm3
	$ make

This will compile the library. Afterwards, change into the src directory and
build the example:

	$ cd ../src
	$ make

Connect your STM32-Discovery board and run 

	$ make flash

to upload the binary into the microcontroller. In order to see the USART output,
connect a 3V3 TTL adaptor to PA2 (USART2_TX). You can use `screen` to see the output:

	$ screen /dev/ttyUSB0 115200


USART Port Mappings
-------------------

Currently, the example uses USART2. The other USART ports can also be used, for example:

* USART1: PB6, PB7
* USART6: PC6, PC7 Note: If you use the STM32F4 Expansion board, the
  UART6 should be mapped to the serial port of this board. However, I
  wasn't able to get this running. Attaching an FTDI USB-TTL-Adapter works fine for these pins.

Tested Host Systems
-------------------

The template has been tested on the following host systems:

* Ubuntu Linux 14.04
* Mac OS Mavericks
