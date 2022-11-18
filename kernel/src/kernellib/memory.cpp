#include "memory.h"

void memcpy(const void* srcPtr, const void* dstPtr, size_t bytes)
{
    char* src = (char*) srcPtr, *dst = (char*) dstPtr;
    for (size_t i = 0; i < bytes; i++)
    {
        dst[i] = src[i];
    }
}

void extract_words(const void* msb, const void* lsb, const void* src, size_t size)
{
    memcpy(src, lsb, size / 2);
    memcpy((char*) src + (size / 2), msb, size / 2);
}

void insert_words(const void* msb, const void* lsb, const void* dst, size_t size)
{
    memcpy(lsb, dst, size);
    memcpy(msb, ((char*) dst) + size, size);
}