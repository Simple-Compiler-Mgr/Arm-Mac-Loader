# ARM64 Bootloader for Apple Silicon Macs / 适用于 Apple Silicon Mac 的 ARM64 引导程序

[English](#english) | [中文](#chinese-1)

---

## English

### Overview
This project is a custom ARM64 bootloader for Apple Silicon Macs, designed to load and boot Android systems using m1n1 or iBoot as a preloader. It provides a minimal, extensible, and highly portable boot environment for ARM64 platforms.

#### Android Boot Process
1. **Preloader Stage (m1n1/iBoot)**
   - Initializes Apple Silicon hardware
   - Sets up secure boot environment
   - Loads our custom bootloader

2. **Custom Bootloader Stage**
   - Parses Android boot image (boot.img)
   - Sets up memory layout for Android
   - Initializes hardware for Android
   - Loads Android kernel, ramdisk, and device tree
   - Transfers control to Android kernel

3. **Android Boot Stage**
   - Android kernel initialization
   - Ramdisk mounting
   - Android system startup
   - Android runtime initialization

#### Supported Android Features
- Standard Android boot image format
- Custom kernel loading
- Ramdisk support
- Device tree (DTB) support
- Android boot parameters
- Android recovery mode
- Android fastboot mode


### Technical Architecture

#### 1. Boot Process
- **Stage 1**: m1n1/iBoot preloader
  - Initializes hardware
  - Sets up memory management
  - Loads our bootloader
- **Stage 2**: Custom Bootloader
  - Parses Android boot image
  - Sets up memory layout
  - Initializes hardware
  - Jumps to kernel

#### 2. Memory Layout
```
0x80000000 - 0x80010000: Bootloader code
0x80010000 - 0x80100000: Stack and heap
0x80100000 - 0x80200000: Android boot image
0x80200000 - 0x80300000: Kernel
0x80300000 - 0x80400000: Ramdisk
0x80400000 - 0x80500000: Device tree
```

#### 3. Key Components

##### Bootloader Core (`src/bootloader.c`)
- Entry point and initialization
- Memory management
- Hardware initialization
- Boot process control

##### Memory Management (`src/memory.c`)
- Memory allocation/deallocation
- Memory protection
- Memory mapping
- Cache management

##### Hardware Interface (`src/hardware.c`)
- UART initialization
- Display controller setup
- Power management
- Clock configuration

##### Android Boot Image Parser (`src/android_boot.c`)
- Boot image format parsing
- Kernel loading
- Ramdisk handling
- Device tree processing

### Development Environment

#### Required Tools
- LLVM/Clang toolchain
- Make
- Python 3.x
- Device Tree Compiler (dtc)

#### Build Dependencies
```bash
# macOS
brew install llvm lld python3 dtc

# Ubuntu/Debian
sudo apt-get install clang lld python3 device-tree-compiler
```

#### Environment Setup
```bash
# Set LLVM toolchain path
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# Build the project
make clean
make
```

### Running Requirements

#### Hardware Requirements
- Apple Silicon Mac (M1/M2/M3)
- USB-C cable for serial console
- USB storage device for Android image

#### Software Requirements
- m1n1 or iBoot as preloader
- Android boot image
- Serial console software (e.g., screen, minicom)

### Technical Details

#### 1. Boot Image Format
The bootloader supports standard Android boot image format:
- Magic: "ANDROID!"
- Kernel size
- Kernel address
- Ramdisk size
- Ramdisk address
- Second stage size
- Second stage address
- Tags address
- Page size
- Header version
- Product name
- Command line
- Extra command line

#### 2. Memory Management
- 4KB page size
- 48-bit virtual address space
- 3-level page tables
- Memory attributes:
  - Normal memory
  - Device memory
  - Write-back cacheable
  - Non-cacheable

#### 3. Hardware Initialization
- UART: 115200 baud, 8N1
- Display: 1920x1080, 32bpp
- Memory: 4GB minimum
- Cache: 64KB L1, 256KB L2

#### 4. Boot Process
1. Preloader initialization
2. Bootloader loading
3. Memory setup
4. Hardware initialization
5. Android image loading
6. Kernel decompression
7. Device tree setup
8. Kernel execution

### API Reference

#### Memory Management
```c
void* mem_alloc(size_t size);
void mem_free(void* ptr);
void mem_init(void);
```

#### Hardware Interface
```c
void uart_init(void);
void uart_putc(char c);
char uart_getc(void);
void display_init(void);
void power_init(void);
```

#### Boot Image Handling
```c
int load_android_image(const char* path);
int parse_boot_image(void* data, size_t size);
int load_kernel(void);
```

### Troubleshooting

#### Common Issues
1. Serial console not working
   - Check baud rate
   - Verify cable connection
   - Check USB port

2. Boot image loading fails
   - Verify image format
   - Check memory size
   - Verify file integrity

3. Kernel panic
   - Check device tree
   - Verify memory layout
   - Check kernel parameters

### Contributing
1. Fork the repository
2. Create feature branch
3. Commit changes
4. Push to branch
5. Create pull request


---

## 中文

### 概述
本项目为 Apple Silicon Mac 设计了一个自定义 ARM64 引导程序，可通过 m1n1 或 iBoot 作为预加载器加载并启动 Android 系统。它提供了极简、可扩展、高度可移植的 ARM64 启动环境。

#### Android 启动流程
1. **预加载器阶段（m1n1/iBoot）**
   - 初始化 Apple Silicon 硬件
   - 设置安全启动环境
   - 加载我们的自定义引导程序

2. **自定义引导程序阶段**
   - 解析 Android 启动镜像（boot.img）
   - 设置 Android 内存布局
   - 初始化 Android 所需硬件
   - 加载 Android 内核、ramdisk 和设备树
   - 跳转到 Android 内核

3. **Android 启动阶段**
   - Android 内核初始化
   - Ramdisk 挂载
   - Android 系统启动
   - Android 运行时初始化

#### 支持的 Android 功能
- 标准 Android 启动镜像格式
- 自定义内核加载
- Ramdisk 支持
- 设备树（DTB）支持
- Android 启动参数
- Android 恢复模式
- Android 快速启动模式

#### Android 系统要求
- Android 版本：Android 11 或更高
- 内核版本：4.19 或更高
- 设备树：支持 ARM64 架构
- 文件系统：ext4/f2fs
- 分区布局：标准 Android 分区表

#### Android 启动参数
```bash
# 基本启动参数
androidboot.hardware=apple
androidboot.serialno=XXXXXXXX
androidboot.mode=normal
androidboot.bootloader=1.0.0

# 调试参数
androidboot.debuggable=1
androidboot.console=ttyS0
androidboot.logcat=v
```

#### Android 设备树要求
```dts
/ {
    compatible = "apple,arm64";
    model = "Apple Silicon Mac";
    
    memory {
        device_type = "memory";
        reg = <0x0 0x80000000 0x0 0x40000000>;
    };
    
    chosen {
        bootargs = "console=ttyS0,115200 androidboot.hardware=apple";
    };
};
```

### 技术架构

#### 1. 启动流程
- **第一阶段**：m1n1/iBoot 预加载器
  - 初始化硬件
  - 设置内存管理
  - 加载我们的引导程序
- **第二阶段**：自定义引导程序
  - 解析 Android 启动镜像
  - 设置内存布局
  - 初始化硬件
  - 跳转到内核

#### 2. 内存布局
```
0x80000000 - 0x80010000: 引导程序代码
0x80010000 - 0x80100000: 栈和堆
0x80100000 - 0x80200000: Android 启动镜像
0x80200000 - 0x80300000: 内核
0x80300000 - 0x80400000: Ramdisk
0x80400000 - 0x80500000: 设备树
```

#### 3. 核心组件

##### 引导程序核心 (`src/bootloader.c`)
- 入口点和初始化
- 内存管理
- 硬件初始化
- 启动流程控制

##### 内存管理 (`src/memory.c`)
- 内存分配/释放
- 内存保护
- 内存映射
- 缓存管理

##### 硬件接口 (`src/hardware.c`)
- UART 初始化
- 显示控制器设置
- 电源管理
- 时钟配置

##### Android 启动镜像解析器 (`src/android_boot.c`)
- 启动镜像格式解析
- 内核加载
- Ramdisk 处理
- 设备树处理

### 开发环境

#### 必需工具
- LLVM/Clang 工具链
- Make
- Python 3.x
- 设备树编译器 (dtc)

#### 构建依赖
```bash
# macOS
brew install llvm lld python3 dtc

# Ubuntu/Debian
sudo apt-get install clang lld python3 device-tree-compiler
```

#### 环境设置
```bash
# 设置 LLVM 工具链路径
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# 构建项目
make clean
make
```

### 运行要求

#### 硬件要求
- Apple Silicon Mac (M1/M2/M3)
- USB-C 串口线
- USB 存储设备（用于 Android 镜像）

#### 软件要求
- m1n1 或 iBoot 作为预加载器
- Android 启动镜像
- 串口终端软件（如 screen、minicom）

### 技术细节

#### 1. 启动镜像格式
引导程序支持标准 Android 启动镜像格式：
- 魔数："ANDROID!"
- 内核大小
- 内核地址
- Ramdisk 大小
- Ramdisk 地址
- 第二阶段大小
- 第二阶段地址
- 标签地址
- 页大小
- 头部版本
- 产品名称
- 命令行
- 额外命令行

#### 2. 内存管理
- 4KB 页大小
- 48位虚拟地址空间
- 3级页表
- 内存属性：
  - 普通内存
  - 设备内存
  - 写回缓存
  - 非缓存

#### 3. 硬件初始化
- UART：115200 波特率，8N1
- 显示：1920x1080，32位色深
- 内存：最小 4GB
- 缓存：64KB L1，256KB L2

#### 4. 启动流程
1. 预加载器初始化
2. 引导程序加载
3. 内存设置
4. 硬件初始化
5. Android 镜像加载
6. 内核解压
7. 设备树设置
8. 内核执行

### API 参考

#### 内存管理
```c
void* mem_alloc(size_t size);
void mem_free(void* ptr);
void mem_init(void);
```

#### 硬件接口
```c
void uart_init(void);
void uart_putc(char c);
char uart_getc(void);
void display_init(void);
void power_init(void);
```

#### 启动镜像处理
```c
int load_android_image(const char* path);
int parse_boot_image(void* data, size_t size);
int load_kernel(void);
```

### 故障排除

#### 常见问题
1. 串口终端不工作
   - 检查波特率
   - 验证线缆连接
   - 检查 USB 端口

2. 启动镜像加载失败
   - 验证镜像格式
   - 检查内存大小
   - 验证文件完整性

3. 内核崩溃
   - 检查设备树
   - 验证内存布局
   - 检查内核参数

### 贡献指南
1. Fork 仓库
2. 创建特性分支
3. 提交更改
4. 推送到分支
5. 创建拉取请求
[English](#english) | [中文](#chinese-1)

---

## English

### Overview
This project is a custom ARM64 bootloader for Apple Silicon Macs, designed to load and boot Android systems using m1n1 or iBoot as a preloader. It provides a minimal, extensible, and highly portable boot environment for ARM64 platforms.

### Latest Development Status
- [x] Basic UART driver implementation
- [x] Initial boot sequence setup
- [x] Memory management framework
- [ ] Android boot image support
- [ ] Device tree handling
- [ ] Kernel loading
- [ ] Ramdisk support

### Project Structure
```
.
├── m1n1/                # m1n1 preloader integration
│   ├── src/            # Source code
│   │   ├── uart.c      # UART driver
│   │   ├── start.S     # Boot entry point
│   │   └── main.c      # Main bootloader code
│   └── build/          # Build output
├── src/                # Bootloader source code
├── include/            # Header files
└── tools/             # Build and development tools
```

### Building and Testing

#### Prerequisites
- LLVM/Clang toolchain
- Make
- Python 3.x
- Device Tree Compiler (dtc)

#### Build Instructions
```bash
# Set up LLVM toolchain
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# Build the project
cd m1n1
make clean
make
```

#### Testing
1. Connect your Apple Silicon Mac to a serial console:
   - Use a USB-C to UART adapter
   - Connect to UART pins (TX/RX/GND)
   - Set baud rate to 115200

2. Run the bootloader:
   ```bash
   # Load m1n1
   python3 tools/run_m1n1.py

   # Monitor serial output
   screen /dev/tty.usbserial* 115200
   ```

3. Expected output:
   ```
   === ARM64 Bootloader ===
   UART initialized
   ```

### Technical Details

#### UART Implementation
- Base address: 0x09000000 (QEMU virt board)
- Baud rate: 115200
- Data format: 8N1
- Features:
  - Basic I/O operations
  - Buffer management
  - Interrupt handling
  - Console support

#### Memory Layout
```
0x80000000 - 0x80010000: Bootloader code
0x80010000 - 0x80100000: Stack and heap
0x80100000 - 0x80200000: Android boot image
0x80200000 - 0x80300000: Kernel
0x80300000 - 0x80400000: Ramdisk
0x80400000 - 0x80500000: Device tree
```

### Contributing
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

### License
This project is licensed under the MIT License - see the LICENSE file for details.

---

## Chinese

### 概述
本项目是一个适用于 Apple Silicon Mac 的自定义 ARM64 引导程序，设计用于通过 m1n1 或 iBoot 作为预加载器来加载和启动 Android 系统。它为 ARM64 平台提供了一个最小化、可扩展且高度可移植的引导环境。

### 最新开发状态
- [x] 基础 UART 驱动实现
- [x] 初始引导序列设置
- [x] 内存管理框架
- [ ] Android 启动镜像支持
- [ ] 设备树处理
- [ ] 内核加载
- [ ] Ramdisk 支持

### 项目结构
```
.
├── m1n1/                # m1n1 预加载器集成
│   ├── src/            # 源代码
│   │   ├── uart.c      # UART 驱动
│   │   ├── start.S     # 引导入口点
│   │   └── main.c      # 主引导程序代码
│   └── build/          # 构建输出
├── src/                # 引导程序源代码
├── include/            # 头文件
└── tools/             # 构建和开发工具
```

### 构建和测试

#### 前置要求
- LLVM/Clang 工具链
- Make
- Python 3.x
- 设备树编译器 (dtc)

#### 构建说明
```bash
# 设置 LLVM 工具链
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# 构建项目
cd m1n1
make clean
make
```

#### 测试
1. 将 Apple Silicon Mac 连接到串口控制台：
   - 使用 USB-C 转 UART 适配器
   - 连接 UART 引脚（TX/RX/GND）
   - 设置波特率为 115200

2. 运行引导程序：
   ```bash
   # 加载 m1n1
   python3 tools/run_m1n1.py

   # 监控串口输出
   screen /dev/tty.usbserial* 115200
   ```

3. 预期输出：
   ```
   === ARM64 Bootloader ===
   UART initialized
   ```

### 技术细节

#### UART 实现
- 基地址：0x09000000（QEMU virt 板）
- 波特率：115200
- 数据格式：8N1
- 功能：
  - 基本 I/O 操作
  - 缓冲区管理
  - 中断处理
  - 控制台支持

#### 内存布局
```
0x80000000 - 0x80010000: 引导程序代码
0x80010000 - 0x80100000: 栈和堆
0x80100000 - 0x80200000: Android 启动镜像
0x80200000 - 0x80300000: 内核
0x80300000 - 0x80400000: Ramdisk
0x80400000 - 0x80500000: 设备树
```

### 贡献
1. Fork 本仓库
2. 创建你的特性分支
3. 提交你的更改
4. 推送到分支
5. 创建 Pull Request

### 许可证
本项目采用 MIT 许可证 - 详见 LICENSE 文件。
