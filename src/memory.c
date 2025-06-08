#include "memory.h"
#include "debug.h"
#include "loader.h"
#include "stdint.h"

// 内存基地址
#define MEMORY_BASE 0x800000000

// 初始化内存
void init_memory(void) {
    debug_print("Memory base: 0x%x", MEMORY_BASE);
    
    // 初始化内存控制器
    // 这里需要根据具体的硬件实现
    
    // 设置栈指针
    __asm__ __volatile__(
        "mov sp, %0\n"
        : : "r" (STACK_ADDR)
    );
    
    debug_print("Memory initialized");
}