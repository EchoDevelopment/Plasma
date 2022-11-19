#include "stdio.h"
#include "core/gdt/gdt.h"
#include "core/idt/idt.h"
#include "core/timer/timer.h"
#include "core/asm/asm.h"
#include "core/interrupts/pic.h"

Framebuffer* framebuffer;
PSF1_FONT* font;
oterminal terminal;

extern "C" void _start(Framebuffer* buffer, PSF1_FONT* defaultFont)
{   
    framebuffer = buffer;
    font = defaultFont; 
    terminal = oterminal{};

    gdt_desc gdtr;
    gdtr.size = sizeof(gdt) - 1;
    gdtr.offset = (size_t)&defaultGDT;
    _loadgdt(&gdtr);

    irq_remap();
    init_idt();
    init_timer();

    sti();

    while (true);
}