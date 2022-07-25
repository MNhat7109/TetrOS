#pragma once
#include <stddef.h>
#include <stdint.h>
#include "math.h"
#include "FrameBuffer.h"
#include "font.h"

class KernelEngine
{
    public:
    Point Position; // Our Text Position
    void putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, const char chr, unsigned int xOff, unsigned int yOff, unsigned int color);
    void Print(FrameBuffer* framebuffer, Psf1_Font* psf1_font, const char* str, unsigned int color = 0xffffffff);
};
// Color
enum vga_color
{
    COLOR_RED = 0xffff0000,
    COLOR_BLUE = 0xff0000ff,
    COLOR_YELLOW = 0xffffff00,
    COLOR_WHITE = 0xffffffff,
};







