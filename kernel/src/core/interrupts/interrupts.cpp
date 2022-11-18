#include "interrupts.h"
#include "stdio.h"

__attribute__((interrupt)) void syscall_int(struct interrupt_frame* frame)
{   
    printf("0x80");
    return;
}
