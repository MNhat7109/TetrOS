# include "KernelEngine.h"
# include "memory/memory.h"

struct BootInfo
{
	FrameBuffer* Framebuffer;
	Psf1_Font* psf1_font;
	efiMemoryDescriptor* mMap;
	uint64_t mMapSize, mMapDescSize;
};
