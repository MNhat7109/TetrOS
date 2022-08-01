# include "KernelEngine.h"
# include "cstr.h"

extern "C" void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(framebuffer, psf1_font); 
	newRenderer.Print(to_string((double)14.15));
	newRenderer.Position = {0,16};
	newRenderer.Print(to_hstring((uint64_t)0xFF00FF00));
    return;
}