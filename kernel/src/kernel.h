#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned long long size_t;

// Color
enum vga_color
{
    COLOR_RED = 0xffff0000,
    COLOR_BLUE = 0xff0000ff,
    COLOR_YELLOW = 0xffffff00,
    COLOR_WHITE = 0xffffffff,
};

typedef struct 
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width; // Screen width
	unsigned int Height; // Screen height
	unsigned int PixelPerScanLine; // This operates just like FPS, really useful there
} FrameBuffer;

typedef struct
{
    unsigned int X; // Height
    unsigned int Y; // Width
} Point;

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

void putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, 
            unsigned int color, char chr, unsigned int xOff, unsigned int yOff) // Puts the character in the screen
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

Point Position; // Our Text Position
void Print(FrameBuffer* framebuffer, Psf1_Font* psf1_font, unsigned int color, char* str) // Prints a string
{
	char* chr = str;
	while (*chr != 0)
	{
		putChar(framebuffer, psf1_font, color, *chr, Position.X, Position.Y);
		Position.X+=8;
		chr++;
	}
}


#endif