#include "stdio.h"
#include "core/gdt/gdt.h"
#include "core/interrupts/idt.h"
#include "core/timer/timer.h"
#include "core/asm/asm.h"
#include "core/interrupts/pic.h"
#include "core/keyboard/keyboard.h"

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

    terminal.write(' ');

    sti();

    while (true)
    {
        for (size_t i = 0; i < 57; i++)
        {
            if (keyboard.shift)
            {
                if (keyboard.isPressed((KeyCode) i)) printf("%c", key_char[i].upper);
            }
            else 
            {
                if (keyboard.isPressed((KeyCode) i)) printf("%c", key_char[i].lower);
            }
        }
    }
}