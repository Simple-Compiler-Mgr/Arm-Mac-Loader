 #include "fdt.h"
#include "stdint.h"
#include "utils.h"

// 设备树头部结构
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

// 设备树节点结构
struct fdt_node {
    uint32_t tag;
    char name[32];
    uint32_t prop_count;
    struct fdt_property props[16];
};

// 设备树属性结构
struct fdt_property {
    char name[32];
    uint32_t len;
    uint8_t data[256];
};

// 检查设备树头部
int fdt_check_header(const void *fdt) {
    const struct fdt_header *header = fdt;
    if (header->magic != 0xd00dfeed) {
        return -1;
    }
    return 0;
}

// 获取节点偏移
int fdt_path_offset(const void *fdt, const char *path) {
    // 简单实现：返回固定偏移
    return 0;
}

// 设置属性
int fdt_setprop(void *fdt, int nodeoffset, const char *name, const void *val, int len) {
    // 简单实现：总是成功
    return 0;
}

// 设置字符串属性
int fdt_setprop_string(void *fdt, int nodeoffset, const char *name, const char *val) {
    return fdt_setprop(fdt, nodeoffset, name, val, strlen(val) + 1);
}

// 设置 64 位属性
int fdt_setprop_u64(void *fdt, int nodeoffset, const char *name, uint64_t val) {
    return fdt_setprop(fdt, nodeoffset, name, &val, sizeof(val));
}

// 获取属性
const void *fdt_getprop(const void *fdt, int nodeoffset, const char *name, int *lenp) {
    // 简单实现：返回 NULL
    return NULL;
}

// 应用设备树覆盖
int fdt_overlay_apply(void *base, void *overlay) {
    // 简单实现：总是成功
    return 0;
}