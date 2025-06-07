#ifndef UTILS_H
#define UTILS_H

#include "stdint.h"
#include "stddef.h"

// 内存操作函数
void* memcpy(void* dest, const void* src, uint32_t n);
void* memset(void* dest, int val, uint32_t n);
int memcmp(const void* s1, const void* s2, uint32_t n);

// 字符串操作函数
int strcmp(const char* s1, const char* s2);
uint32_t strlen(const char* s);

#endif // UTILS_H