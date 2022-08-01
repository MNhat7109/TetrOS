# include "KernelEngine.h"
# include "cstr.h"

extern "C" void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(framebuffer, psf1_font); 
	newRenderer.Print(to_string((int64_t)-123456));
    return;
}