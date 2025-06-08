#ifndef LOADER_H
#define LOADER_H

#include "stdint.h"

// 内存布局
#define DTB_ADDR     0x80000000
#define KERNEL_ADDR  0x80200000
#define RAMDISK_ADDR 0x80300000
#define RAMDISK_SIZE 0x1000000
#define STACK_ADDR   0x90000000

// 启动参数结构
struct boot_params {
    uint64_t dtb_addr;
    uint64_t kernel_addr;
    uint64_t ramdisk_addr;
    uint64_t ramdisk_size;
};

// 加载设备树
int load_dtb(void);

// 加载内核
int load_kernel(void);

// 加载 ramdisk
int load_ramdisk(void);

// 主加载函数
int loader_main(void);

// 跳转到内核
void jump_to_kernel(struct boot_params *params);

#endif // LOADER_H