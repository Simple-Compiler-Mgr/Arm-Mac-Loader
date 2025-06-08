# 编译器设置
CROSS_COMPILE = aarch64-elf-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

# 编译选项
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -Iinclude \
         -march=armv8-a -mtune=cortex-a53 -mstrict-align \
         -fno-stack-protector -fomit-frame-pointer
ASFLAGS = -march=armv8-a
LDFLAGS = -nostdlib -T linker.ld

# 源文件和目标文件
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
SRCS = $(wildcard $(SRC_DIR)/*.c)
ASRCS = $(wildcard $(SRC_DIR)/*.S)
#OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
       $(ASRCS:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
OBJS = src/start.o src/uart.o src/bootloader.o src/load.o

bootloader.bin: $(OBJS)
	aarch64-elf-ld -T linker.ld -o bootloader.elf $(OBJS)
	aarch64-elf-objcopy -O binary bootloader.elf bootloader.bin

src/%.o: src/%.c
	aarch64-elf-gcc -c $< -o $@ -Iinclude

src/%.o: src/%.S
	aarch64-elf-gcc -c $< -o $@ -Iinclude

# 目标文件
TARGET = $(BUILD_DIR)/bootloader.elf
BIN = $(BUILD_DIR)/bootloader.bin

# 默认目标
all: $(BUILD_DIR) $(BIN)

# 创建构建目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 编译规则
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	$(CC) $(CFLAGS) -c $< -o $@

# 链接规则
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# 生成二进制文件
$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

# 清理规则
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean