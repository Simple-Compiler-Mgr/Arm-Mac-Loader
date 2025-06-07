#ifndef BOOTIMG_H
#define BOOTIMG_H

#include "stdint.h"

#define BOOT_MAGIC "ANDROID!"
#define BOOT_MAGIC_SIZE 8
#define BOOT_NAME_SIZE 16
#define BOOT_ARGS_SIZE 512
#define BOOT_EXTRA_ARGS_SIZE 1024

struct boot_img_hdr {
    uint8_t magic[BOOT_MAGIC_SIZE];
    uint32_t kernel_size;
    uint32_t kernel_addr;
    uint32_t ramdisk_size;
    uint32_t ramdisk_addr;
    uint32_t second_size;
    uint32_t second_addr;
    uint32_t tags_addr;
    uint32_t page_size;
    uint32_t header_version;
    uint32_t os_version;
    uint8_t name[BOOT_NAME_SIZE];
    uint8_t cmdline[BOOT_ARGS_SIZE];
    uint32_t id[8];
    uint8_t extra_cmdline[BOOT_EXTRA_ARGS_SIZE];
    uint32_t recovery_dtbo_size;
    uint64_t recovery_dtbo_offset;
    uint32_t header_size;
    uint32_t dtb_size;
    uint64_t dtb_addr;
} __attribute__((packed));

// boot.img 解析函数
int parse_bootimg(const uint8_t *boot_img, struct boot_img_hdr *header);
int extract_kernel_from_bootimg(const uint8_t *boot_img, uint8_t **kernel, uint32_t *kernel_size);
int extract_ramdisk_from_bootimg(const uint8_t *boot_img, uint8_t **ramdisk, uint32_t *ramdisk_size);
int extract_dtb_from_bootimg(const uint8_t *boot_img, uint8_t **dtb, uint32_t *dtb_size);

#endif // BOOTIMG_H