#ifndef LOADER_H
#define LOADER_H

#include "stdint.h"

// Apple Silicon 内存布局 (从 8GB 开始，避免与 m1n1 冲突)
#define BOOT_IMG_ADDR    0x800000000  // boot.img 加载地址 (8GB)
#define KERNEL_ADDR      0x800800000  // 内核加载地址
#define RAMDISK_ADDR     0x810000000  // ramdisk 加载地址
#define DTB_ADDR         0x8F0000000  // dtb 加载地址
#define STACK_ADDR       0x900000000  // 栈地址

// 内存大小定义
#define BOOT_IMG_SIZE    (64 * 1024 * 1024)  // 64MB
#define KERNEL_SIZE      (32 * 1024 * 1024)  // 32MB
#define RAMDISK_SIZE     (256 * 1024 * 1024) // 256MB
#define DTB_SIZE         (4 * 1024 * 1024)   // 4MB

// 初始化内存布局
void init_memory(void);

// 加载并启动内核
int load_kernel(void);

// 从 boot.img 中提取内核
int extract_kernel(uint8_t *boot_img, uint32_t size, uint8_t **kernel, uint32_t *kernel_size);

// 初始化串口（用于调试）
void init_uart(void);

// 打印调试信息
void debug_print(const char *fmt, ...);

#endif // LOADER_H