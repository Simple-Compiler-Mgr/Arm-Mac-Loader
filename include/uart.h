#ifndef UART_H
#define UART_H

// 初始化 UART
void init_uart(void);

// 发送一个字符
void uart_putc(char c);

// 发送字符串
void uart_puts(const char* s);

#endif // UART_H