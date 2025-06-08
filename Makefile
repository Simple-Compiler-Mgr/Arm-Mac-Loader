# 编译器设置
CROSS_COMPILE = arm-none-eabi-
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
OBJS = src/start.o src/uart.o src/bootloader.o src/bootloader_stub.o

bootloader.bin: $(OBJS)
	$(LD) -T linker.ld -o bootloader.elf $(OBJS)
	$(OBJCOPY) -O binary bootloader.elf bootloader.bin

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

src/%.o: src/%.S
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则
clean:
	rm -f $(OBJS) bootloader.elf bootloader.bin

.PHONY: all clean