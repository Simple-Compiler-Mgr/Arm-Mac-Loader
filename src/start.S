.section .text.boot
.global _start

_start:
    // 初始化 UART
    bl uart_init
    
    // 输出启动信息
    mov w0, 'A'
    bl uart_send
    mov w0, '\r'
    bl uart_send
    mov w0, '\n'
    bl uart_send
    
    // 设置栈指针
    ldr x1, =_stack_top
    mov sp, x1
    
    // 跳转到 main
    bl main
    
    // 如果 main 返回，进入死循环
    b .