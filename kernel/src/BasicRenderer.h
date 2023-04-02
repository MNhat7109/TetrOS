#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h" 
#include <stdint.h>

# define COLOR(_r, _g, _b)((uint8_t))(\
    (((_r) & 0x7) << 5) |       \
    (((_g) & 0x7) << 2) |       \
    (((_b) & 0x3) << 0))
class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF2_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF2_FONT* PSF2_Font;
    unsigned int Colour;
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void Clear(uint32_t colour);
    void Next();
};

extern BasicRenderer* GlobalRenderer;