 ENTRY(_start)

SECTIONS
{
    . = 0x800000000;  /* 8GB 处开始 */

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }

    /* 栈从 9GB 处开始向下增长 */
    . = 0x900000000;
    .stack : {
        . = . + 0x1000000;  /* 16MB 栈空间 */
    }
}