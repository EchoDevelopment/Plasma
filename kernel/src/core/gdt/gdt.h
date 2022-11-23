#pragma once

struct gdt_desc
{
    uint16_t size;
    uint64_t offset;
} __attribute__((packed));

struct gdt_entry
{
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access_byte;
    uint8_t limit1_flags;
    uint8_t base2;
} __attribute__((packed));

struct gdt
{
    gdt_entry null;
    gdt_entry code;
    gdt_entry data;
} __attribute__((packed))
__attribute__((aligned(0x1000)));

extern gdt defaultGDT;

extern "C" void _loadgdt(gdt_desc* gdtr);