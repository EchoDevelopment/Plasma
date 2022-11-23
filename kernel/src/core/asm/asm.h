#pragma once

// Useful assembly wrapped up as functions
#define cli() asm ("cli")
#define sti() asm ("sti")

static inline uint16_t in(uint16_t port) {
    uint16_t r;
    asm("inw %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void out(uint16_t port, uint16_t data) {
    asm("outw %1, %0" : : "dN" (port), "a" (data));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t r;
    asm("inb %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void outb(uint16_t port, uint8_t data) {
    asm("outb %1, %0" : : "dN" (port), "a" (data));
}

static inline void io_wait()
{
    
}