#pragma once

struct Framebuffer 
{
	void* BaseAddr;
	size_t BufferSize;
	unsigned int width, height, pixelsPerScanline;
};