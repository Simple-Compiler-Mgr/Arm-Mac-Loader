# 设备树编译器
DTC = dtc

# 源文件和目标文件
DTS = apple_silicon.dts
DTB = apple_silicon.dtb

# 默认目标
all: $(DTB)

# 编译设备树
$(DTB): $(DTS)
	$(DTC) -I dts -O dtb -o $@ $<

# 清理
clean:
	rm -f $(DTB)

.PHONY: all clean