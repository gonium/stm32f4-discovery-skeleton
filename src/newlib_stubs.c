#include <errno.h>
#include <unistd.h>
#include <libopencm3/stm32/usart.h>

#define USART_CONSOLE USART2

/**
 * prototypes
 */
int _write(int file, char *ptr, int len);
//caddr_t _sbrk(int incr);

/**
 * implementations below
 */

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
//caddr_t _sbrk(int incr) {
//
//    extern char _ebss; // Defined by the linker
//    static char *heap_end;
//    char *prev_heap_end;
//
//    if (heap_end == 0) {
//        heap_end = &_ebss;
//    }
//    prev_heap_end = heap_end;
//
//	char * stack = (char*) __get_MSP();
//	if (heap_end + incr >  stack) {
//         _write (STDERR_FILENO, "Heap and stack collision\n", 25);
//         errno = ENOMEM;
//         return  (caddr_t) -1;
//         //abort ();
//     }
//
//    heap_end += incr;
//    return (caddr_t) prev_heap_end;
//
//}

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

