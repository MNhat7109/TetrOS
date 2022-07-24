# include "KernelEngine.h"
# include "FrameBuffer.h"
# include "math.h"
# include "font.h"


extern "C" void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
	// Class declarations
	KernelEngine newRenderer; 

	// Text Positions
	newRenderer.Position = {15,50}; // Sets xy coordinates, x is width and y is height

	// Print!
	newRenderer.Print(framebuffer, psf1_font, "It's tetris time");
    return;
}