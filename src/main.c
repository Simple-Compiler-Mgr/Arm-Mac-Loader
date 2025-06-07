#include "loader.h"
#include "dtb.h"
#include "stdint.h"

// 引导入口点
void _start(void) {
    // 初始化串口用于调试
    init_uart();
    debug_print("Starting bootloader...");
    
    // 初始化内存
    debug_print("Initializing memory...");
    init_memory();
    
    // 加载设备树
    debug_print("Loading device tree...");
    if (load_dtb() != 0) {
        debug_print("Failed to load device tree!");
        while(1);
    }
    
    // 加载并启动内核
    debug_print("Loading kernel...");
    if (load_kernel() != 0) {
        debug_print("Failed to load kernel!");
        while(1);
    }
    
    // 不应该到达这里
    debug_print("Unexpected return from kernel load!");
    while(1);
}