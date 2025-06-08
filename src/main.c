#include "debug.h"
#include "loader.h"
#include "uart.h"
#include "memory.h"
#include "stdint.h"

int main(void) {
    // 初始化 UART
    init_uart();
    debug_print("Starting bootloader...");
    
    // 初始化内存
    init_memory();
    
    // 加载设备树
    if (load_dtb() != 0) {
        debug_print("Failed to load device tree!");
        return -1;
    }
    
    // 加载内核
    if (load_kernel() != 0) {
        debug_print("Failed to load kernel!");
        return -1;
    }
    
    // 加载 ramdisk
    if (load_ramdisk() != 0) {
        debug_print("Failed to load ramdisk!");
        return -1;
    }
    
    // 启动系统
    return loader_main();
}