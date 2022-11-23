#include "idt.h"
#include "interrupts.h"
#include "pic.h"

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

void setup_int(uint8_t vec, uint64_t offset, uint8_t attributes)
{
    idt_entry* entry = &idt[vec];
    entry->setOffset(offset);
    entry->attributes = attributes;
    entry->kernel_cs = 0x08;
}

void setup_irq(uint8_t vec, uint64_t offset, uint8_t attributes)
{
    irq_clear_mask(vec - 0x20);
    setup_int(vec, offset, attributes);
}

void init_idt()
{
    idtdesc.limit = 0x0FFF;
    idtdesc.base = (uint64_t)idt;

    setup_int(0x80, (uint64_t)syscall_int, IDTINTGATE);
    setup_irq(0x20, (uint64_t)timer_int, IDTINTGATE);
    setup_irq(0x21, (uint64_t)keyboard_int, IDTINTGATE);

    for (size_t i = 0; i < 0x20; i++)
    {
        setup_int(i, (uint64_t)error_handler, IDTINTGATE);
    }

    __asm__ volatile ("lidt %0" : : "m" (idtdesc)); // load the new IDT
}