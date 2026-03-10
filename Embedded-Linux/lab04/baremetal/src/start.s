.section .text
.global _start

_start:
    /* CRITICAL: Set up stack pointer */
    ldr     x0, =__stack_top    /* Get stack top address from linker script */
    mov     sp, x0               /* Set stack pointer */
    
    /* Optional: Clear BSS */
    ldr     x0, =__bss_start
    ldr     x1, =__bss_end
    mov     x2, #0
1:  cmp     x0, x1
    b.ge    2f
    str     x2, [x0], #8
    b       1b
2:
    /* Call main */
    bl      main
    
    /* If main returns, loop forever */
halt:
    b       halt
