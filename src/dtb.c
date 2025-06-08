#include "dtb.h"
#include "fdt.h"
#include "debug.h"
#include "utils.h"
#include "stdint.h"
#include "stddef.h"

// 内存布局常量
#define MEMORY_BASE 0x800000000
#define MEMORY_SIZE 0x400000000

// 设备树加载地址
#define DTB_LOAD_ADDR 0x80000000

// 加载设备树
int dtb_load(const char* path) {
    debug_print("Loading device tree from %s", path);
    
    // 从内存中读取设备树
    void *dtb = (void *)DTB_LOAD_ADDR;
    
    // 验证设备树魔数
    if (fdt_check_header(dtb) != 0) {
        debug_print("Invalid device tree!");
        return -1;
    }
    
    // 设置设备树属性
    if (fdt_setprop_string(dtb, 0, "compatible", "apple,arm64") < 0) {
        debug_print("Failed to set compatible property!");
        return -1;
    }
    
    // 设置内存节点
    int memory_node = fdt_path_offset(dtb, "/memory");
    if (memory_node < 0) {
        debug_print("Memory node not found!");
        return -1;
    }
    
    // 设置内存大小
    uint64_t mem_size = MEMORY_SIZE;
    if (fdt_setprop_u64(dtb, memory_node, "reg", mem_size) < 0) {
        debug_print("Failed to set memory size!");
        return -1;
    }
    
    // 设置启动参数
    int chosen_node = fdt_path_offset(dtb, "/chosen");
    if (chosen_node < 0) {
        debug_print("Chosen node not found!");
        return -1;
    }
    
    const char *bootargs = "console=ttyS0,115200 androidboot.hardware=apple androidboot.mode=normal";
    if (fdt_setprop_string(dtb, chosen_node, "bootargs", bootargs) < 0) {
        debug_print("Failed to set bootargs!");
        return -1;
    }
    
    debug_print("Device tree loaded successfully");
    return 0;
}

// 应用设备树覆盖
int dtb_apply_overlay(void* base, void* overlay) {
    debug_print("Applying device tree overlay");
    
    // 验证基础设备树
    if (fdt_check_header(base) != 0) {
        debug_print("Invalid base device tree!");
        return -1;
    }
    
    // 验证覆盖设备树
    if (fdt_check_header(overlay) != 0) {
        debug_print("Invalid overlay device tree!");
        return -1;
    }
    
    // 应用覆盖
    int ret = fdt_overlay_apply(base, overlay);
    if (ret != 0) {
        debug_print("Failed to apply overlay: %d", ret);
        return -1;
    }
    
    debug_print("Device tree overlay applied successfully");
    return 0;
}

// 获取设备树属性
const void* dtb_get_property(const char* path, const char* propname, int* len) {
    void *dtb = (void *)DTB_LOAD_ADDR;
    int node = fdt_path_offset(dtb, path);
    if (node < 0) {
        return NULL;
    }
    
    return fdt_getprop(dtb, node, propname, len);
}

// 设置设备树属性
int dtb_set_property(const char* path, const char* propname, const void* val, int len) {
    void *dtb = (void *)DTB_LOAD_ADDR;
    int node = fdt_path_offset(dtb, path);
    if (node < 0) {
        return -1;
    }
    
    return fdt_setprop(dtb, node, propname, val, len);
}

// 解析设备树
int parse_dtb(void* dtb) {
    if (!dtb) {
        return -1;
    }
    
    const struct fdt_header *header = dtb;
    if (header->magic != 0xd00dfeed) {
        return -1;
    }
    
    return 0;
}

// 获取设备树中的内存信息
int get_memory_info(uint64_t *base, uint64_t *size) {
    if (!base || !size) {
        return -1;
    }
    
    *base = MEMORY_BASE;
    *size = MEMORY_SIZE;
    return 0;
}