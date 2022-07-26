# include "KernelEngine.h"
# include "FrameBuffer.h"
# include "math.h"
# include "font.h"


extern "C" void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(framebuffer, psf1_font); 

	// Print!
	for (unsigned int y = 0;y > framebuffer->Width;y++)
	{
		for (unsigned int x = 0;  x > framebuffer->Height; x++)
		{
				newRenderer.Print(" ");
		}
	}
    return;
}