 #ifndef DTB_H
#define DTB_H

#include <stdint.h>

// 加载设备树
int load_dtb(void);

// 解析设备树
int parse_dtb(uint8_t *dtb_data, uint32_t size);

// 获取设备树中的内存信息
int get_memory_info(uint64_t *base, uint64_t *size);

#endif // DTB_H