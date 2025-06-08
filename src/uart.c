#include "uart.h"
#include "stdint.h"

// UART 基地址 (QEMU virt 板的 UART 地址)
#define UART_BASE 0x09000000

// UART 寄存器偏移
#define UART_DR    0x00
#define UART_FR    0x18
#define UART_IBRD  0x24
#define UART_FBRD  0x28
#define UART_LCR_H 0x2C
#define UART_CR    0x30

// UART 状态位
#define UART_FR_TXFF (1 << 5)
#define UART_FR_RXFE (1 << 4)
#define UART_LCR_H_FEN (1 << 4)
#define UART_LCR_H_WLEN_8BIT (3 << 5)
#define UART_CR_UARTEN (1 << 0)
#define UART_CR_TXE (1 << 8)
#define UART_CR_RXE (1 << 9)

// 初始化 UART
void uart_init(void) {
    // 禁用 UART
    *(volatile uint32_t*)(UART_BASE + UART_CR) = 0;
    
    // 设置波特率 (115200)
    // 系统时钟频率为 50MHz
    // 波特率 = 115200
    // IBRD = 50MHz / (16 * 115200) = 27.1267
    // FBRD = 0.1267 * 64 + 0.5 = 8.6
    *(volatile uint32_t*)(UART_BASE + UART_IBRD) = 27;
    *(volatile uint32_t*)(UART_BASE + UART_FBRD) = 8;
    
    // 设置数据格式：8位数据，1位停止位，无校验
    *(volatile uint32_t*)(UART_BASE + UART_LCR_H) = UART_LCR_H_WLEN_8BIT | UART_LCR_H_FEN;
    
    // 启用 UART，启用发送和接收
    *(volatile uint32_t*)(UART_BASE + UART_CR) = UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE;
}

// 发送一个字符
void uart_send(char c) {
    // 等待发送缓冲区为空
    while (*(volatile uint32_t*)(UART_BASE + UART_FR) & UART_FR_TXFF);
    
    // 发送字符
    *(volatile uint32_t*)(UART_BASE + UART_DR) = c;
}

// 接收一个字符
char uart_getc(void) {
    // 等待接收缓冲区非空
    while (*(volatile uint32_t*)(UART_BASE + UART_FR) & UART_FR_RXFE);
    
    // 读取字符
    return *(volatile uint32_t*)(UART_BASE + UART_DR) & 0xFF;
}

// 发送字符串
void uart_puts(const char* s) {
    while (*s) {
        uart_send(*s++);
    }
}