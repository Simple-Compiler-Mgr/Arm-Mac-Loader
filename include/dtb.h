#ifndef DTB_H
#define DTB_H

#include "stdint.h"

// 设备树加载
int dtb_load(const char* path);

// 设备树覆盖
int dtb_apply_overlay(void* base, void* overlay);

// 获取设备树属性
const void* dtb_get_property(const char* path, const char* propname, int* len);

// 设置设备树属性
int dtb_set_property(const char* path, const char* propname, const void* val, int len);

// 设备树解析
int parse_dtb(void* dtb);

// 获取内存信息
int get_memory_info(uint64_t *base, uint64_t *size);

#endif // DTB_H