# include "BootInfo.h"
# include "cstr.h"

extern "C" void _start(BootInfo* bootInfo)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(bootInfo->Framebuffer, bootInfo->psf1_font); 

	newRenderer.Print(to_string((double)14.15));
	newRenderer.Position = {0,16};
	newRenderer.Print(to_hstring((uint16_t)0xABCD));
    return;
}