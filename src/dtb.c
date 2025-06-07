#include "dtb.h"
#include "stdint.h"
#include "loader.h"

// 简单的设备树结构
struct fdt_header {
    uint32_t magic;
    uint32_t totalsize;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
};

// 加载设备树
int load_dtb(void) {
    debug_print("Loading device tree...");
    
    // 1. 创建基本的设备树
    struct fdt_header *dtb = (struct fdt_header *)DTB_ADDR;
    
    // 2. 设置设备树头部
    dtb->magic = 0xd00dfeed;  // FDT_MAGIC
    dtb->version = 17;        // 设备树版本
    dtb->last_comp_version = 16;
    dtb->boot_cpuid_phys = 0;
    
    // 3. 设置内存节点
    // 这里需要添加内存节点，描述可用的物理内存
    
    debug_print("Device tree loaded at 0x%x", DTB_ADDR);
    return 0;
}

// 解析设备树
int parse_dtb(uint8_t *dtb_data, uint32_t size) {
    if (!dtb_data || size < sizeof(struct fdt_header)) {
        return -1;
    }
    
    struct fdt_header *dtb = (struct fdt_header *)dtb_data;
    if (dtb->magic != 0xd00dfeed) {
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