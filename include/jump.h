 #ifndef JUMP_H
#define JUMP_H

#include <stdint.h>

// 跳转到内核入口点
void jump_to_kernel(uint64_t kernel_addr, uint64_t dtb_addr, uint64_t ramdisk_addr);

// 设置启动参数
void setup_boot_params(uint64_t kernel_addr, uint64_t dtb_addr, uint64_t ramdisk_addr);

#endif // JUMP_H