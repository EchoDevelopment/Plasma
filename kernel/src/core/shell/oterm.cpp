#include "oterm.h"
#include "str.h"
#include <cstdarg>

extern Framebuffer* framebuffer;
extern PSF1_FONT* font;

oterminal::oterminal()
{
    this->pos = {0, 0};
    this->color = (unsigned int) Color::WHITE;
    for (int y = 0; y < framebuffer->height; y++)
    {
        for (int x = 0; x < framebuffer->width * 4; x+=4)
        {
            writePix(x, y, (unsigned int) Color::BLACK);
        }
    }
}

oterminal::oterminal(Vec2i pos)
{
    setPos(pos);
    this->color = (unsigned int) Color::WHITE;
    for (int y = 0; y < framebuffer->height; y++)
    {
        for (int x = 0; x < framebuffer->width * 4; x+=4)
        {
            writePix(x, y, (unsigned int) Color::BLACK);
        }
    }
}

oterminal::oterminal(unsigned int color)
{
    this->pos = {0, 0};
    this->color = (unsigned int) color;
    for (int y = 0; y < framebuffer->height; y++)
    {
        for (int x = 0; x < framebuffer->width * 4; x+=4)
        {
            writePix(x, y, (unsigned int) Color::BLACK);
        }
    }
}

oterminal::oterminal(Vec2i pos, unsigned int color)
{
    setPos(pos);
    this->color = (unsigned int) color;
    for (int y = 0; y < framebuffer->height; y++)
    {
        for (int x = 0; x < framebuffer->width * 4; x+=4)
        {
            writePix(x, y, (unsigned int) Color::BLACK);
        }
    }
}

void oterminal::clearScreen()
{
    for (int y = 0; y < framebuffer->height; y++)
    {
        for (int x = 0; x < framebuffer->width * 4; x+=4)
        {
            writePix(x, y, (unsigned int) Color::BLACK);
        }
    }
}

// Printing functions

// Puts a single character onto screen location
void oterminal::putChar(char chr)
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddr;
    char* fontPtr = ((char*)font->characterBuffer) + (chr * font->header->charsize);
    for (unsigned long y = pos.y; y < pos.y + 16; y++)
    {
        for (unsigned long x = pos.x; x < pos.x + 8; x++)
        {
            // some complex bitwise math to determine if a pixel should be shaded
            if ((*fontPtr & (0b10000000 >> (x - pos.x))) > 0)
            {
                *(unsigned int*)(pixPtr + x + (y * framebuffer->pixelsPerScanline)) = color;
            }
        }
        fontPtr++;
    }
}

// Prints a single character onto the screen, but formatted and increments cursor position
bool oterminal::write(char chr)
{
    if (chr == 0) return 0;
    switch (chr)
    {
        case '\n':
            pos.x = 0;
            pos.y += 16;
            break;
        default:
            if (pos.x > framebuffer->width) 
            {
                pos.x = 0;
                pos.y += 16;
            }
            putChar(chr);
            pos.x+=8;
            break;
    }
    
    return 1;
}

// Prints a c-style string to the screen, with helper functions for special characters
void oterminal::print(const char* str)
{
    while (write(*str)) str++;
}

void oterminal::printui(unsigned long long value)
{
    tostr(value);
    print(valueToStringOut);
}

void oterminal::printi(long long value)
{
    tostr(value);
    print(valueToStringOut);
}

void oterminal::printd(double value)
{
    tostr(value);
    print(valueToStringOut);
}

void oterminal::printh(uint64_t value)
{
    tohex(value);
    print("0x");
    print(valueToStringOut);
}

void oterminal::printh(uint32_t value)
{
    tohex(value);
    print("0x");
    print(valueToStringOut);
}

void oterminal::printh(uint16_t value)
{
    tohex(value);
    print("0x");
    print(valueToStringOut);
}

void oterminal::printh(uint8_t value)
{
    tohex(value);
    print("0x");
    print(valueToStringOut);
}

// Printf: a simple printf implemetation that supports integers, doubles, strings, hexadecimal values, and bools
void oterminal::printf(const char* str, ...)
{
    va_list args;
    va_start(args, str);
    vaprintf(str, args);
    va_end(args);
}

void oterminal::vaprintf(const char* str, va_list args)
{
    while (*str != 0) 
    {
        switch (*str)
        {
            case '%':
            {
                str++;
                switch (*str)
                {
                    case 'b':
                        if (va_arg(args, int)) print("True");
                        else print("False");
                        break;
                    case 'd':
                        printd(va_arg(args, double));
                        break;
                    case 'i':
                        str++;
                        switch (*str)
                        {
                            case 'h':
                                str++;
                                if (*str == 'h') printi((char) va_arg(args, int));
                                else 
                                {
                                    printi((short) va_arg(args, int));
                                    str--;
                                }
                                break;
                            case 'l':
                                str++;
                                if (*str == 'l') printi(va_arg(args, long long));
                                else 
                                {
                                    printi(va_arg(args, long));
                                    str--;
                                }
                                break;
                            default:
                                printi(va_arg(args, int));
                                str--;
                                break;
                        }
                        break;
                    case 'u':
                        str++;
                        switch (*str)
                        {
                            case 'h':
                                str++;
                                if (*str == 'h') printui((unsigned char) va_arg(args, int));
                                else 
                                {
                                    printui((unsigned short) va_arg(args, int));
                                    str--;
                                }
                                break;
                            case 'l':
                                str++;
                                if (*str == 'l') printui(va_arg(args, long long));
                                else 
                                {
                                    printui(va_arg(args, long));
                                    str--;
                                }
                                break;
                            default:
                                printui(va_arg(args, unsigned int));
                                str--;
                                break;
                        }
                        break;
                    case 'x':
                        str++;
                        switch (*str)
                        {
                            case 'h':
                                str++;
                                if (*str == 'h') printh((unsigned char) va_arg(args, int));
                                else 
                                {
                                    printh((unsigned short) va_arg(args, int));
                                    str--;
                                }
                                break;
                            case 'l':
                                str++;
                                if (*str == 'l') printh(va_arg(args, unsigned long long));
                                else 
                                {
                                    printh(va_arg(args, unsigned long long));
                                    str--;
                                }
                                break;
                            default:
                                printh(va_arg(args, unsigned int));
                                str--;
                                break;
                        }
                        break;
                    case 'c':
                        write((char) va_arg(args, int));
                        break;
                    case 's':
                        print(va_arg(args, const char*));
                        break;
                    case 'n':
                        break;
                    case '%':
                        write('%');
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                write(*str);
                break;
        }
        str++;
    }
}

void oterminal::setPos(Vec2i pos)
{
    if (pos.x > framebuffer->width) return;
    if (pos.y > framebuffer->height) return;
    this->pos = pos;
}

void oterminal::setColor(unsigned int color)
{
    this->color = color;
}

// Write a single pixel, used to clear the screen to black
void oterminal::writePix(unsigned int x, unsigned int y, unsigned int color)
{
    *(unsigned int*)(x + (y * framebuffer->pixelsPerScanline * 4) + (char*)framebuffer->BaseAddr) = color;
}

