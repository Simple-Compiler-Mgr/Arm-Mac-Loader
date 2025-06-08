ENTRY(_start)

SECTIONS
{
    . = 0x40080000;

    .text : {
        *(.text.boot)
        *(.text)
    }

    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;
    }

    . = ALIGN(4096);
    _stack_bot = .;
    . += 0x10000;  /* 64KB 栈空间 */
    _stack_top = .;
}