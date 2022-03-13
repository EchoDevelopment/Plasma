typedef unsigned long long size_t;

typedef struct {
	void* BaseAddr;
	size_t BufferSize;
	unsigned int width, height, pixelsPerScanline;
} Framebuffer;

typedef struct 
{
	unsigned char identifier[2];
	unsigned char mode;
	unsigned char charsize;
} PSF1_HEADER;

typedef struct 
{
	PSF1_HEADER* header;
	void* characterBuffer;
} PSF1_FONT;

Framebuffer* framebuffer;
PSF1_FONT* currentFont;

void putChar(unsigned int color, char chr, unsigned int xoff, unsigned int yoff)
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddr;
    char* fontPtr = currentFont->characterBuffer + (chr * currentFont->header->charsize);
    for (unsigned long y = yoff; y < yoff + 16; y++)
    {
        for (unsigned long x = xoff; x < xoff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xoff))) > 0)
            {
                *(unsigned int*)(pixPtr + x + (y * framebuffer->pixelsPerScanline)) = color;
            }
        }
        fontPtr++;
    }
}

void print(unsigned int color, const char* str)
{
    unsigned int x = 8;
    while(*str != 0)
    {
        putChar(color, *str, x, 0);
        x+=8;
        str++;
    }
}

void _start(Framebuffer* buffer, PSF1_FONT* font)
{   
    framebuffer = buffer;
    currentFont = font; 
    print(0xffffffff, "Hello, kernel");

    return;
}