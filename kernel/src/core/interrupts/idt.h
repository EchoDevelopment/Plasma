#pragma once

#define IDTINTGATE  0b10001110
#define IDTCALLGATE 0b10001100
#define IDTTRAPGATE 0b10001111

struct idt_entry
{
	uint16_t offset0;      // The lower 16 bits of the ISR's address
	uint16_t kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t attributes;   // Type and attributes; see the IDT page
	uint16_t offset1;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t offset2;     // The higher 32 bits of the ISR's address
	uint32_t reserved;     // Set to zero
    void setOffset(uint64_t offset);
    uint64_t getOffset();
} __attribute__((packed));

struct idtr 
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

__attribute__((aligned(0x1000)))
extern idt_entry idt[256];

__attribute__((aligned(0x1000)))
extern idtr idtdesc;

void init_idt();

