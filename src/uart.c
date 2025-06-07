#include "loader.h"
#include "stdarg.h"
#include "stdint.h"

// Apple Silicon UART 寄存器定义
#define UART_BASE 0x235200000  // UART 基地址
#define UART_DR   (UART_BASE + 0x0)   // 数据寄存器
#define UART_FR   (UART_BASE + 0x18)  // 标志寄存器
#define UART_IBRD (UART_BASE + 0x24)  // 整数波特率除数
#define UART_FBRD (UART_BASE + 0x28)  // 小数波特率除数
#define UART_LCRH (UART_BASE + 0x2C)  // 线路控制寄存器
#define UART_CR   (UART_BASE + 0x30)  // 控制寄存器

// ... rest of the file remains unchanged ...

// 初始化 UART
void init_uart(void) {
    // 禁用 UART
    *(volatile uint32_t *)UART_CR = 0;
    
    // 设置波特率 (115200)
    *(volatile uint32_t *)UART_IBRD = 26;
    *(volatile uint32_t *)UART_FBRD = 3;
    
    // 设置数据格式 (8N1)
    *(volatile uint32_t *)UART_LCRH = (1 << 4) | (1 << 5) | (1 << 6);
    
    // 启用 UART
    *(volatile uint32_t *)UART_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

// 发送一个字符
static void uart_putc(char c) {
    // 等待发送缓冲区空
    while (*(volatile uint32_t *)UART_FR & (1 << 5));
    
    // 发送字符
    *(volatile uint32_t *)UART_DR = c;
}

// 打印字符串
static void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

// 打印十六进制数
static void uart_putx(uint64_t x) {
    char hex[] = "0123456789ABCDEF";
    char buf[20];
    int i = 0;
    
    if (x == 0) {
        uart_puts("0x0");
        return;
    }
    
    uart_puts("0x");
    while (x) {
        buf[i++] = hex[x & 0xF];
        x >>= 4;
    }
    
    while (i > 0) {
        uart_putc(buf[--i]);
    }
}

// 打印调试信息
void debug_print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's':
                    uart_puts(va_arg(args, char *));
                    break;
                case 'x':
                    uart_putx(va_arg(args, uint64_t));
                    break;
                case 'd':
                    // 简单的十进制打印
                    {
                        int val = va_arg(args, int);
                        char buf[20];
                        int i = 0;
                        
                        if (val < 0) {
                            uart_putc('-');
                            val = -val;
                        }
                        
                        if (val == 0) {
                            uart_putc('0');
                        } else {
                            while (val) {
                                buf[i++] = '0' + (val % 10);
                                val /= 10;
                            }
                            while (i > 0) {
                                uart_putc(buf[--i]);
                            }
                        }
                    }
                    break;
                default:
                    uart_putc(*fmt);
            }
        } else {
            uart_putc(*fmt);
        }
        fmt++;
    }
    
    va_end(args);
    uart_putc('\n');
}