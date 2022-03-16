#include "stdio.h"

Framebuffer* framebuffer;
PSF1_FONT* font;
oterminal terminal;

extern "C" void _start(Framebuffer* buffer, PSF1_FONT* defaultFont)
{   
    framebuffer = buffer;
    font = defaultFont; 
    terminal = oterminal{};
    printf("Hello, printf%d", 9.2344);

    while (true);
}