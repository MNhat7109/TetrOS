#pragma once
#include <stddef.h>
#include <stdint.h>
#include "math.h"
#include "FrameBuffer.h"
#include "font.h"

class KernelEngine
{
    public:
    KernelEngine(FrameBuffer* TargetFramebuffer, Psf1_Font* Psf1_font);
    Point Position; // Our Text Position
    FrameBuffer* TargetFramebuffer;
    Psf1_Font* Psf1_font;
    unsigned int Color;
    void putChar( const char chr, unsigned int xOff, unsigned int yOff);
    void Print(const char* str);
    void Clear(void);
};
// Color
enum vga_color
{
    COLOR_RED = 0xffff0000,
    COLOR_BLUE = 0xff0000ff,
    COLOR_YELLOW = 0xffffff00,
    COLOR_WHITE = 0xffffffff,
};







