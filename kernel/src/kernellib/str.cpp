#include "str.h"

char out_str[128];

void _ulltoc(uint64_t value, char* output)
{
    uint8_t size;
    uint64_t sizeTest = value;

    while(sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while(value / 10 > 0)
    {
        uint8_t remainder = value % 10;
        value /= 10;
        output[size - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    output[size - index] = remainder + '0';
    output[size + 1] = 0;
}

void itoa(uint64_t value)
{
    _ulltoc(value, out_str);
}

void itoa(int64_t value)
{
    if (value < 0)
    {
        out_str[0] = '-';
        value *= -1;
    }

    _ulltoc(value, &out_str[value < 0]);
}

void htoa(uint64_t value)
{
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        out_str[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        out_str[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    out_str[size + 1] = 0;
}

void htoa(uint32_t value)
{
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        out_str[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        out_str[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    out_str[size + 1] = 0;
}

void htoa(uint16_t value)
{
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 * 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        out_str[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        out_str[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    out_str[size + 1] = 0;
}

void htoa(uint8_t value)
{
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        out_str[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        out_str[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    out_str[size + 1] = 0;
}

void _dtocd(double value, uint8_t places)
{
    itoa((int64_t)value);
    char* doublePtr = (char*) out_str + strlen(out_str) + 1;

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int64_t) value;

    for (uint8_t i = 0; i < places; i++)
    {
        newValue *= 10;
        *doublePtr = (char) newValue + '0';
        newValue -= (int64_t) newValue;
        doublePtr++;
    }

    *doublePtr = 0;
}

void dtoa(double value)
{
    _dtocd(value, 6);

    // Eliminate remaining zeros
    size_t size = strlen(out_str);
    for (char* i = out_str + size; *i == '0'; i--) *i = 0;
}

// Returns the length of a null-terminated string, up to (but not including) the null character
size_t strlen(const char* str)
{
    size_t size = 0;
    for (; *(str + size + 1) != 0; size++);
    return size;
}