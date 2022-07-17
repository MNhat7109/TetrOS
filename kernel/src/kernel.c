# include "kernel.h"
typedef unsigned long long size_t;

typedef struct 
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width; // Screen width
	unsigned int Height; // Screen height
	unsigned int PixelPerScanLine; // This operates just like FPS, really useful there
} FrameBuffer;

void _start(FrameBuffer* framebuffer)
{
    unsigned int y = 50; // Pixels down the screen we want to pass
	unsigned int BBP = 4; // 4 bytes per pixel

	for (unsigned int x = 0; x < framebuffer->Width / 2 * BBP; x+=BBP)
	{
		*(unsigned int*)(x + (y * framebuffer->PixelPerScanLine*BBP)+framebuffer->BaseAddress) = COLOR_YELLOW; // green
	}

    return;
}