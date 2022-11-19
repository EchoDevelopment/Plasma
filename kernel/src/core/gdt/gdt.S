.code64
.text

.global _loadgdt
_loadgdt:
    cli
    lgdt (%rdi)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    popq %rdi
    mov $0x08, %rax
    pushq %rax
    pushq %rdi
    lretq
    