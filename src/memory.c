#include "loader.h"
#include "stdint.h"

// 内存布局定义
#define MEMORY_BASE 0x800000000  // 8GB
#define MEMORY_SIZE 0x100000000  // 4GB

// 初始化内存布局
void init_memory(void) {
    // 1. 设置内存控制器（在 Apple Silicon 上，这部分由 m1n1 处理）
    debug_print("Memory base: 0x%x", MEMORY_BASE);
    debug_print("Memory size: 0x%x", MEMORY_SIZE);

    // 2. 初始化页表（可选，如果需要启用 MMU）
    // 在初始阶段，我们可以先不使用 MMU，直接使用物理地址

    // 3. 设置栈指针
    asm volatile(
        "mov sp, %0"
        : : "r" (STACK_ADDR)
    );
    debug_print("Stack initialized at 0x%x", STACK_ADDR);

    // 4. 清除 BSS 段（如果需要）
    // 在裸机环境中，这部分可能不需要

    debug_print("Memory initialization completed");
}

// 内存分配函数（简单实现）
void* mem_alloc(uint32_t size) {
    static uint64_t current_addr = MEMORY_BASE;
    void* ptr = (void*)current_addr;
    current_addr += size;
    return ptr;
}

// 内存释放函数（简单实现）
void mem_free(void* ptr) {
    // 在初始阶段，我们不需要实现内存释放
    (void)ptr;
}