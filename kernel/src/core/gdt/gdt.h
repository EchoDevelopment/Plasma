#pragma once

struct GDTDesc
{
    uint16_t size;
    uint64_t offset;
} __attribute__((packed));

struct GDTEntry
{
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access_byte;
    uint8_t limit1_flags;
    uint8_t base2;
} __attribute__((packed));

struct GDT
{
    GDTEntry null;
    GDTEntry code;
    GDTEntry data;
} __attribute__((packed))
__attribute__((aligned(0x1000)));

extern GDT defaultGDT;

extern "C" void _loadgdt(GDTDesc* gdtd);