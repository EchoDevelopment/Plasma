#include "gdt.h"

__attribute__((aligned(0x1000)))
gdt defaultGDT = 
{
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0x9a, 0b10100000, 0},
    {0, 0, 0, 0x92, 0b11000000, 0},
};