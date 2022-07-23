#include "KernelEngine.h"
#include "FrameBuffer.h"

void KernelEngine::putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, 
            unsigned int color, const char chr, unsigned int xOff, unsigned int yOff) // Puts the character in the screen
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

void KernelEngine::Print(FrameBuffer* framebuffer, Psf1_Font* psf1_font, unsigned int color, const char* str) // Prints a string
{
	char* chr = (char*)str;
	while (*chr != 0)
	{
		putChar(framebuffer, psf1_font, color, *chr, Position.X, Position.Y);
		Position.X+=8;
		chr++;
	}
}
