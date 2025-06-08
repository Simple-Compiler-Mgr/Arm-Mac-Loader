#include "debug.h"
#include "uart.h"
#include "stdint.h"

// 调试打印函数
void debug_print(const char* fmt, ...) {
    uart_puts(fmt);
    uart_putc('\n');
}