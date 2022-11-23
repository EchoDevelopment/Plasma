#include "interrupts.h"
#include "pic.h"
#include "stdio.h"
#include "core/timer/timer.h"
#include "core/asm/asm.h"
#include "core/keyboard/keyboard.h"

__attribute__((interrupt)) void error_handler(struct interrupt_frame* frame)
{
    printf("Fault %i", frame->err_no);
    asm ("hlt");
}

__attribute__((interrupt)) void syscall_int(struct interrupt_frame* frame)
{   
    printf("0x80");
}

__attribute__((interrupt)) void timer_int(struct interrupt_frame* frame)
{
    sys_timer.ticks++;
    if (sys_timer.ticks == sys_timer.fq)
    {
        sys_timer.ticks = 0;
        sys_timer.seconds++;
    }
    eoi(0x20);
}

__attribute__((interrupt)) void keyboard_int(struct interrupt_frame* frame)
{
    keyboard.input_scancode(inb(0x60));
    eoi(0x21);
}