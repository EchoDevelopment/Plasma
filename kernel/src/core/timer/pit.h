#pragma once

// IO Ports
#define PIT_C0 0x40
#define PIT_C1 0x41
#define PIT_C2 0x42
#define PIT_MODE 0x43

void set_pit_mode(uint8_t mode);
void set_pit_freq(uint16_t hz);