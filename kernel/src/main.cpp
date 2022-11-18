#include "stdio.h"
#include "core/gdt/gdt.h"
#include "core/idt/idt.h"

Framebuffer* framebuffer;
PSF1_FONT* font;
oterminal terminal;

extern "C" void _start(Framebuffer* buffer, PSF1_FONT* defaultFont)
{   
    framebuffer = buffer;
    font = defaultFont; 
    terminal = oterminal{};

    GDTDesc gdtd;
    gdtd.size = sizeof(GDT) - 1;
    gdtd.offset = (size_t)&defaultGDT;
    _loadgdt(&gdtd);

    init_idt();

    __asm__ volatile ("int $0x80");

    printf("Done");

    while (true);
}