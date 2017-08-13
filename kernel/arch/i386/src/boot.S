# Declare constants for the multiboot header.
.set MB_ALIGN,    1<<0             # align loaded modules on page boundaries
.set MB_MEMINFO,  1<<1             # provide memory map
#.set MB_GRAPHICS, 1<<2             # graphics video info provided
.set MB_FLAGS,    MB_ALIGN | MB_MEMINFO #| MB_GRAPHICS
.set MB_MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set MB_CHECKSUM, -(MB_MAGIC + MB_FLAGS) # checksum of above, to prove we are multiboot

.section .multiboot
.align 4
.long MB_MAGIC
.long MB_FLAGS
.long MB_CHECKSUM

.section .bss
.align 16
stack_begin:
.skip 512 # 0.5 KiB
stack_end:

.section .text
.global _start
.type _start, @function
_start:
    movl $stack_end, %esp
    pushl %esp
    pushl %ebx # Preserve multiboot mem map info
    pushl %eax # Preserve multiboot magic
    call arch_init
    call _init # Global constructors.
    call k_main
    cli
.global halt
.type halt, @function
halt:
    hlt
    jmp halt
.size _start, . - _start
