#include "KernelEngine.h"
#include "FrameBuffer.h"

void KernelEngine::putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, const char chr, unsigned int xOff, unsigned int yOff, unsigned int color = 0xffffffff) // Puts the character in the screen
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = (char*)psf1_font->glyphBuffer + (chr * psf1_font->psf1_header->charsize);
    for (unsigned long y = yOff; y < yOff+16; y++)
    {
        for (unsigned long x = xOff; x < xOff+8; x++)
        {
            // Checks if the bit is on or off
            if ((*fontPtr & (0b10000000 >> (x-xOff))) > 0)
            {
                *(unsigned int*)(pixPtr+x+(y*framebuffer->PixelPerScanLine)) = color;
            }
        }
        fontPtr++;
    }
}

void KernelEngine::Print(FrameBuffer* framebuffer, Psf1_Font* psf1_font, const char* str, unsigned int color = 0xffffffff) // Prints a string
{
	char* chr = (char*)str;
	while (*chr != 0)
	{
		putChar(framebuffer, psf1_font, *chr, Position.X, Position.Y, color);
		Position.X+=8;
		
        if (Position.X + 8 > framebuffer->Width || chr == "\n")
        {
            Position.X = 0;
            Position.Y +=16;
        }
        chr++;
	}
}
