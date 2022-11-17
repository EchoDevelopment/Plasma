#pragma once

struct interrupt_frame;
__attribute__((interrupt)) void syscall_int(struct interrupt_frame* frame);