#include "pic.h"

#define PIC1 0x20
#define PIC1_OFFSET 0x20
#define PIC1_DATA 0x21

#define PIC2 0xA0
#include "pic.h"
#include "core/asm/asm.h"

#define PIC2_OFFSET 0x28
#define PIC2_DATA 0xA1

#define PIC_EOI 0x20
#define PIC_MODE_8086 0x01
#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10

void irq_remap()
{
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);
    outb(PIC1, ICW1_INIT | ICW1_ICW4);
    outb(PIC2, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, PIC1_OFFSET);
    outb(PIC2_DATA, PIC2_OFFSET);
    outb(PIC1_DATA, 0x04); // PIC2 at IRQ2
    outb(PIC2_DATA, 0x02); // Cascade indentity
    outb(PIC1_DATA, PIC_MODE_8086);
    outb(PIC1_DATA, PIC_MODE_8086);
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void eoi(char intv)
{
    // send EOI
    if (intv >= 0x28) {
        outb(PIC2, PIC_EOI);
    }

    outb(PIC1, PIC_EOI);
}