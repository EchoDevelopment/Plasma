#pragma once

#include "core/graphics/Framebuffer.h"
#include "core/graphics/Font.h"
#include "stdinc.h"
#include <cstdarg>

class oterminal
{
private:
    Vec2i pos;
    unsigned int color;
public:
    oterminal();
    oterminal(Vec2i pos);
    oterminal(unsigned int color);
    oterminal(Vec2i pos, unsigned int color);

    // put a character onto the screen
    void putChar(char chr);

    // All the print functions you need
    bool write(char chr);
    void print(const char* str);
    void printi(long long i);
    void printui(unsigned long long i);
    void printd(double d);
    void printh(uint64_t i);
    void printh(uint32_t i);
    void printh(uint16_t i);
    void printh(uint8_t i);
    void printf(const char*, ...);
    void vaprintf(const char*, va_list args);

    // Setters
    void setPos(Vec2i pos);
    void setColor(unsigned int color);

    // Clear screen
    void clearScreen();

private:
    void writePix(unsigned int x, unsigned int y, unsigned int color);
};