#include "idt.h"
#include "core/interrupts/interrupts.h"

__attribute__((aligned(0x1000)))
idt_entry idt[256];

__attribute__((aligned(0x1000)))
idtr idtdesc;

void idt_entry::setOffset(uint64_t offset)
{
    this->offset0 = (uint16_t)(offset & 0x000000000000FFFF);
    this->offset1 = (uint16_t)((offset & 0x00000000FFFF0000) >> 16);
    this->offset2 = (uint32_t)((offset & 0xFFFFFFFF00000000) >> 32);
}

uint64_t idt_entry::getOffset()
{
    return (uint64_t) offset0 | (uint64_t) (offset1 << 16) | (((uint64_t) offset2) << 32);
}

void init_idt()
{
    idtdesc.limit = 0x0FFF;
    idtdesc.base = (uint64_t)idt;

    idt_entry* test = &idt[0x80];
    test->setOffset((uint64_t)syscall_int);
    test->attributes = IDTINTGATE;
    test->kernel_cs = 0x08;

    __asm__ volatile ("lidt %0" : : "m" (idtdesc)); // load the new IDT
}