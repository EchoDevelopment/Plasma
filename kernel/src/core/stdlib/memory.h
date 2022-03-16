#pragma once

void memcpy(const void* src, const void* dst, size_t bytes);

void extract_words(const void* msb, const void* lsb, const void* src, size_t size);
void insert_words(const void* msb, const void* lsb, const void* dst, size_t size);