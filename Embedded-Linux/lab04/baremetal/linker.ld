ENTRY(_start)

SECTIONS
{
    . = 0x80000;
    /* Remove __start = .; - it's conflicting */

    .text : {
        *start.o (.text)    /* Put startup code first */
        *(.text)            /* Then all other code */
    }

    .rodata : { *(.rodata) }
    .data : { *(.data) }

    __bss_start = .;
    .bss : { *(.bss) }
    __bss_end = .;

    . = ALIGN(16);
    . += 0x10000;
    __stack_top = .;

    __end = .;
}