#pragma once

extern char out_str[128];

void itoa(uint64_t value);
void itoa(int64_t value);
void htoa(uint64_t value);
void htoa(uint32_t value);
void htoa(uint16_t value);
void htoa(uint8_t value);
void dtoa(double value);

size_t strlen(const char* str);
