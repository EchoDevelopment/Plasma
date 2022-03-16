#include "str.h"
#include "math/round.h"

char valueToStringOut[128];

void tostrAtPtr(uint64_t value, char* output)
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

void tostr(uint64_t value)
{
    tostrAtPtr(value, valueToStringOut);
}

void tostr(int64_t value)
{
    uint8_t isNeg = false;

    if (value < 0)
    {
        isNeg = true;
        value *= -1;
        valueToStringOut[0] = '-';
    }

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
        valueToStringOut[size + isNeg - index] = remainder + '0';
        index++;
    }
    uint8_t remainder = value % 10;
    valueToStringOut[size + isNeg- index] = remainder + '0';
    valueToStringOut[size + isNeg + 1] = 0;
}

void tohex(uint64_t value)
{
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8 * 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        valueToStringOut[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        valueToStringOut[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    valueToStringOut[size + 1] = 0;
}

void tohex(uint32_t value)
{
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 4 * 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        valueToStringOut[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        valueToStringOut[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    valueToStringOut[size + 1] = 0;
}

void tohex(uint16_t value)
{
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 * 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        valueToStringOut[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        valueToStringOut[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    valueToStringOut[size + 1] = 0;
}

void tohex(uint8_t value)
{
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 2 - 1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        valueToStringOut[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        valueToStringOut[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }

    valueToStringOut[size + 1] = 0;
}

void tostr(double value, uint8_t decimalPlaces)
{
    tostr((int64_t)value);
    char* doublePtr = (char*) valueToStringOut + strlen(valueToStringOut) + 1;

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int64_t) value;

    for (uint8_t i = 0; i < decimalPlaces; i++)
    {
        newValue *= 10;
        *doublePtr = (char) newValue + '0';
        newValue -= (int64_t) newValue;
        doublePtr++;
    }

    *doublePtr = 0;
}

void tostr(double value)
{ 
    tostr((int64_t)value);
    char* doublePtr = (char*) valueToStringOut + strlen(valueToStringOut) + 1;

    *doublePtr = '.';
    doublePtr++;

    double onlyDec = value - (int64_t) value;
    uint64_t roundedDec = round(value * 100000); 

    tostrAtPtr(roundedDec, doublePtr);

    // Eliminate remaining zeros
    size_t size = strlen(valueToStringOut);
    for (char* i = valueToStringOut + size; *i == '0'; i--) *i = 0;

}

// Returns the length of a null-terminated string, up to (but not including) the null character
size_t strlen(const char* str)
{
    size_t size = 0;
    for (; *(str + size + 1) != 0; size++);
    return size;
}