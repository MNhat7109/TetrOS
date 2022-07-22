# include "kernel.h"
typedef struct 
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width; // Screen width
	unsigned int Height; // Screen height
	unsigned int PixelPerScanLine; // This operates just like FPS, really useful there
} FrameBuffer;

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

void putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, unsigned int color, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
    char* fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->psf1_header->charsize);
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

void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
    // unsigned int y = 0.5; // Pixels down the screen we want to pass
	// unsigned int BBP = 4; // 4 bytes per pixel

	// for (y; y < framebuffer->Height/2*BBP; y+=0.5+BBP)
	// {
	// 	for (unsigned int x = 0; x < framebuffer->Width  * BBP; x+=BBP)
	// 	{
	// 		*(unsigned int*)(x + (y * framebuffer->PixelPerScanLine*BBP)+framebuffer->BaseAddress) = COLOR_BLUE; // green
	// 	}
	// }
	putChar(framebuffer, psf1_font, 0xffffffff, 'G', 50, 50);

    return;
}