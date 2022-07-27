# include "KernelEngine.h"
# include "FrameBuffer.h"
# include "math.h"
# include "font.h"


extern "C" void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(framebuffer, psf1_font); 

	unsigned int BBP = 4;
	
	for (unsigned int y = 0; y < 50; y++)
	{
		for (unsigned int x = 0; x < framebuffer->Width; x++)
		{
			*(unsigned int*)(x+(y*framebuffer->Width*BBP)+(unsigned int*)framebuffer->BaseAddress) = 0xffff0000;
		}
	}
    return;
}