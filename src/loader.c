#include "loader.h"
#include "utils.h"
#include "dtb.h"
#include "debug.h"
#include "stdint.h"
#include "stddef.h"

// 加载设备树
int load_dtb(void) {
    debug_print("Loading device tree...");
    
    // 加载基础设备树
    if (dtb_load("dtb/apple_silicon.dtb") != 0) {
        debug_print("Failed to load base device tree!");
        return -1;
    }
    
    // 设置设备树属性
    const char *bootargs = "console=ttyS0,115200 androidboot.hardware=apple androidboot.mode=normal";
    if (dtb_set_property("/chosen", "bootargs", bootargs, strlen(bootargs) + 1) < 0) {
        debug_print("Failed to set bootargs!");
        return -1;
    }
    
    debug_print("Device tree loaded successfully");
    return 0;
}

// 加载内核
int load_kernel(void) {
    debug_print("Loading kernel...");
    
    // 从内存中读取内核
    void *kernel = (void *)KERNEL_ADDR;
    
    // 验证内核魔数
    if (*(uint32_t *)kernel != 0x644d5241) { // ARM64 魔数
        debug_print("Invalid kernel!");
        return -1;
    }
    
    debug_print("Kernel loaded successfully");
    return 0;
}

// 加载 ramdisk
int load_ramdisk(void) {
    debug_print("Loading ramdisk...");
    
    // 从内存中读取 ramdisk
    void *ramdisk = (void *)RAMDISK_ADDR;
    
    // 验证 ramdisk 大小
    uint32_t size = *(uint32_t *)ramdisk;
    if (size > RAMDISK_SIZE) {
        debug_print("Ramdisk too large!");
        return -1;
    }
    
    debug_print("Ramdisk loaded successfully");
    return 0;
}

// 主加载函数
int loader_main(void) {
    debug_print("Starting bootloader...");
    
    // 1. 加载设备树
    if (load_dtb() != 0) {
        debug_print("Failed to load device tree!");
        return -1;
    }
    
    // 2. 加载内核
    if (load_kernel() != 0) {
        debug_print("Failed to load kernel!");
        return -1;
    }
    
    // 3. 加载 ramdisk
    if (load_ramdisk() != 0) {
        debug_print("Failed to load ramdisk!");
        return -1;
    }
    
    // 4. 准备启动参数
    struct boot_params params;
    params.dtb_addr = DTB_ADDR;
    params.kernel_addr = KERNEL_ADDR;
    params.ramdisk_addr = RAMDISK_ADDR;
    params.ramdisk_size = RAMDISK_SIZE;
    
    // 5. 跳转到内核
    debug_print("Jumping to kernel...");
    jump_to_kernel(&params);
    
    // 不应该到达这里
    return -1;
}