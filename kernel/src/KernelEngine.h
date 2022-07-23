#pragma once
#include <stddef.h>
#include <stdint.h>
#include "math.h"
#include "FrameBuffer.h"

class KernelEngine
{
    public:
    Point Position; // Our Text Position
    void putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, unsigned int color, const char chr, unsigned int xOff, unsigned int yOff);
    void Print(FrameBuffer* framebuffer, Psf1_Font* psf1_font, unsigned int color, const char* str);
}
// Color
enum vga_color
{
    COLOR_RED = 0xffff0000,
    COLOR_BLUE = 0xff0000ff,
    COLOR_YELLOW = 0xffffff00,
    COLOR_WHITE = 0xffffffff,
};



// Font file header struct
typedef struct
{
	unsigned char magic[2]; // Magic bytes
	unsigned char mode; // PSF Mode
	unsigned char charsize; // Character size in bytes
} Psf1_Header;

// Font struct
typedef struct
{
	Psf1_Header* psf1_header; // Header
	void* glyphBuffer;
} Psf1_Font;




