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
    unsigned int y = 0.5; // Pixels down the screen we want to pass
	unsigned int BBP = 4; // 4 bytes per pixel

	for (y; y < framebuffer->Height/2*BBP; y+=0.5+BBP)
	{
		for (unsigned int x = 0; x < framebuffer->Width  * BBP; x+=BBP)
		{
			*(unsigned int*)(x + (y * framebuffer->PixelPerScanLine*BBP)+framebuffer->BaseAddress) = COLOR_BLUE; // green
		}
	}

    return;
}