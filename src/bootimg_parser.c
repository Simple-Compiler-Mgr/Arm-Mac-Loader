#include "bootimg.h"
#include "utils.h"
#include "stdint.h"
#include "stddef.h"

// 解析 boot.img
int parse_bootimg(const uint8_t *boot_img, struct boot_img_hdr *header) {
    if (!boot_img || !header) {
        return -1;
    }

    // 复制头部数据
    memcpy(header, boot_img, sizeof(struct boot_img_hdr));

    // 验证魔数
    if (memcmp(header->magic, BOOT_MAGIC, BOOT_MAGIC_SIZE) != 0) {
        return -1;
    }

    return 0;
}

// 从 boot.img 中提取内核
int extract_kernel_from_bootimg(const uint8_t *boot_img, uint8_t **kernel, uint32_t *kernel_size) {
    struct boot_img_hdr header;
    if (parse_bootimg(boot_img, &header) != 0) {
        return -1;
    }

    // 计算内核偏移
    uint32_t kernel_offset = header.page_size;
    
    // 分配内存并复制内核
    *kernel = (uint8_t *)boot_img + kernel_offset;
    *kernel_size = header.kernel_size;

    return 0;
}

// 从 boot.img 中提取 ramdisk
int extract_ramdisk_from_bootimg(const uint8_t *boot_img, uint8_t **ramdisk, uint32_t *ramdisk_size) {
    struct boot_img_hdr header;
    if (parse_bootimg(boot_img, &header) != 0) {
        return -1;
    }

    if (header.ramdisk_size == 0) {
        *ramdisk = NULL;
        *ramdisk_size = 0;
        return 0;
    }

    // 计算 ramdisk 偏移
    uint32_t ramdisk_offset = header.page_size + 
                            ((header.kernel_size + header.page_size - 1) & ~(header.page_size - 1));
    
    // 分配内存并复制 ramdisk
    *ramdisk = (uint8_t *)boot_img + ramdisk_offset;
    *ramdisk_size = header.ramdisk_size;

    return 0;
}

// 从 boot.img 中提取 dtb
int extract_dtb_from_bootimg(const uint8_t *boot_img, uint8_t **dtb, uint32_t *dtb_size) {
    struct boot_img_hdr header;
    if (parse_bootimg(boot_img, &header) != 0) {
        return -1;
    }

    if (header.dtb_size == 0) {
        *dtb = NULL;
        *dtb_size = 0;
        return 0;
    }

    // 计算 dtb 偏移
    uint32_t dtb_offset = header.recovery_dtbo_offset;
    
    // 分配内存并复制 dtb
    *dtb = (uint8_t *)boot_img + dtb_offset;
    *dtb_size = header.dtb_size;

    return 0;
}