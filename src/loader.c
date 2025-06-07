#include "loader.h"
#include "bootimg.h"
#include "jump.h"
#include "utils.h"
#include "stdint.h"
#include "stddef.h"

// 加载并启动内核
int load_kernel(void) {
    struct boot_img_hdr header;
    uint8_t *kernel = NULL;
    uint8_t *ramdisk = NULL;
    uint8_t *dtb = NULL;
    uint32_t kernel_size = 0;
    uint32_t ramdisk_size = 0;
    uint32_t dtb_size = 0;
    
    debug_print("Loading boot.img from 0x%x", BOOT_IMG_ADDR);
    
    // 从内存中读取 boot.img
    uint8_t *boot_img = (uint8_t *)BOOT_IMG_ADDR;
    
    // 解析 boot.img
    debug_print("Parsing boot.img header...");
    if (parse_bootimg(boot_img, &header) != 0) {
        debug_print("Failed to parse boot.img header!");
        return -1;
    }
    
    debug_print("Boot.img version: %d", header.header_version);
    debug_print("Kernel size: %d bytes", header.kernel_size);
    debug_print("Ramdisk size: %d bytes", header.ramdisk_size);
    debug_print("DTB size: %d bytes", header.dtb_size);
    
    // 提取内核
    debug_print("Extracting kernel...");
    if (extract_kernel_from_bootimg(boot_img, &kernel, &kernel_size) != 0) {
        debug_print("Failed to extract kernel!");
        return -1;
    }
    
    // 提取 ramdisk
    debug_print("Extracting ramdisk...");
    if (extract_ramdisk_from_bootimg(boot_img, &ramdisk, &ramdisk_size) != 0) {
        debug_print("Failed to extract ramdisk!");
        return -1;
    }
    
    // 提取 dtb
    debug_print("Extracting DTB...");
    if (extract_dtb_from_bootimg(boot_img, &dtb, &dtb_size) != 0) {
        debug_print("Failed to extract DTB!");
        return -1;
    }
    
    // 将内核复制到目标地址
    debug_print("Copying kernel to 0x%x", header.kernel_addr);
    memcpy((void *)(uintptr_t)header.kernel_addr, kernel, kernel_size);
    
    // 将 ramdisk 复制到目标地址（如果有）
    if (ramdisk_size > 0) {
        debug_print("Copying ramdisk to 0x%x", header.ramdisk_addr);
        memcpy((void *)(uintptr_t)header.ramdisk_addr, ramdisk, ramdisk_size);
    }
    
    // 将 dtb 复制到目标地址（如果有）
    if (dtb_size > 0) {
        debug_print("Copying DTB to 0x%x", header.dtb_addr);
        memcpy((void *)(uintptr_t)header.dtb_addr, dtb, dtb_size);
    }
    
    debug_print("Jumping to kernel at 0x%x", header.kernel_addr);
    
    // 跳转到内核
    jump_to_kernel(header.kernel_addr, header.dtb_addr, header.ramdisk_addr);
    
    return 0;
}