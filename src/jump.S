.section .text
.global jump_to_kernel
jump_to_kernel:
    // 保存参数
    mov x0, x0  // 内核地址
    mov x1, x1  // 设备树地址
    mov x2, x2  // ramdisk 地址
    
    // 禁用 MMU
    mrs x3, sctlr_el1
    bic x3, x3, #1
    msr sctlr_el1, x3
    
    // 跳转到内核
    br x0 