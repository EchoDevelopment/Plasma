#include "pit.h"
#include "core/asm/asm.h"

void set_pit_mode(uint8_t mode)
{
    outb(PIT_MODE, mode);
}

void set_pit_freq(uint16_t hz)
{
    cli();
    outb(PIT_C0, (1193181 / hz)&0xFF);
    outb(PIT_C0, ((1193181 / hz)&0xFF00) >> 8);
}