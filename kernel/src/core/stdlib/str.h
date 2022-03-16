#pragma once

extern char valueToStringOut[128];

void tostr(uint64_t value);
void tostr(int64_t value);
void tohex(uint64_t value);
void tohex(uint32_t value);
void tohex(uint16_t value);
void tohex(uint8_t value);
void tostr(double value, uint8_t decimalPlaces);
void tostr(double value);

size_t strlen(const char* str);
