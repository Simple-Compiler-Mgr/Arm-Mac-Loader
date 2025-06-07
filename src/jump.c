#include "jump.h"
#include "stdint.h"

// 设置启动参数
void setup_boot_params(uint64_t kernel_addr, uint64_t dtb_addr, uint64_t ramdisk_addr) {
    // 设置 x0 寄存器为 dtb 地址
    register uint64_t x0 asm("x0") = dtb_addr;
    
    // 设置 x1 寄存器为 ramdisk 地址
    register uint64_t x1 asm("x1") = ramdisk_addr;
    
    // 设置 x2 寄存器为 0（保留）
    register uint64_t x2 asm("x2") = 0;
    
    // 设置 x3 寄存器为 0（保留）
    register uint64_t x3 asm("x3") = 0;
    
    // 确保寄存器值被使用
    asm volatile("" : : "r" (x0), "r" (x1), "r" (x2), "r" (x3));
}

// 跳转到内核入口点
void jump_to_kernel(uint64_t kernel_addr, uint64_t dtb_addr, uint64_t ramdisk_addr) {
    // 设置启动参数
    setup_boot_params(kernel_addr, dtb_addr, ramdisk_addr);
    
    // 禁用中断
    asm volatile("msr daifset, #0xf");
    
    // 跳转到内核
    asm volatile(
        "mov x30, %0\n"
        "ret"
        : : "r" (kernel_addr)
    );
    
    // 不应该到达这里
    while(1);
}