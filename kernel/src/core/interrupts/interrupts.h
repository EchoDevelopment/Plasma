#pragma once

struct interrupt_frame
{
    uint32_t __ignored, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_no;
    uint32_t eip, cs, efl, useresp, ss;
};

__attribute__((interrupt)) void error_handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void syscall_int(struct interrupt_frame* frame);
__attribute__((interrupt)) void timer_int(struct interrupt_frame* frame);
__attribute__((interrupt)) void keyboard_int(struct interrupt_frame* frame);