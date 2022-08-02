#include "KernelEngine.h"
#include "FrameBuffer.h"

KernelEngine::KernelEngine(FrameBuffer* targetFramebuffer, Psf1_Font* psf1_font)
{
    TargetFramebuffer = targetFramebuffer;
    Psf1_font = psf1_font;
    Color = 0xffffffff;
    Position = {0,0};
}

void KernelEngine::putChar(const char chr, unsigned int xOff, unsigned int yOff) // Puts the character in the screen
{
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    char* fontPtr = (char*)Psf1_font->glyphBuffer + (chr * Psf1_font->psf1_header->charsize);
    for (unsigned long y = yOff; y < yOff+16; y++)
    {
        for (unsigned long x = xOff; x < xOff+8; x++)
        {
            // Checks if the bit is on or off
            if ((*fontPtr & (0b10000000 >> (x-xOff))) > 0)
            {
                *(unsigned int*)(pixPtr+x+(y*TargetFramebuffer->PixelPerScanLine)) = Color;
            }
        }
        fontPtr++;
    }
}

void KernelEngine::Print(const char* str) // Prints a string
{
	char* chr = (char*)str;
	while (*chr != 0)
	{
		putChar(*chr, Position.X, Position.Y);
		Position.X+=8;
		
        if (Position.X + 8 > TargetFramebuffer->Width)
        {
            Position.X = 0;
            Position.Y +=16;
        }
        if (*chr == '\n')
        {            
            chr+='\0';
            Position.X = 0;
            Position.Y += 16;
        }
        chr++;
	}
}

void KernelEngine::Clear(void)
{
    
}