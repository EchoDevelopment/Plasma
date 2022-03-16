#pragma once

struct PSF1_HEADER
{
	unsigned char identifier[2];
	unsigned char mode;
	unsigned char charsize;
};

struct PSF1_FONT
{
	PSF1_HEADER* header;
	void* characterBuffer;
};

enum class Color : unsigned int
{
	BLACK = 0x00000000, 
	WHITE = 0x00ffffff, 
	RED = 0x00ff0000, 
	GREEN = 0x0000ff00, 
	BLUE = 0x000000ff, 
	YELLOW = 0x00ffff00, 
	ORANGE = 0x00ff6600,
	PURPLE = 0x00ffff00
};