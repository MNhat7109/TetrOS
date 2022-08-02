# include "KernelEngine.h"

struct BootInfo
{
	FrameBuffer* Framebuffer;
	Psf1_Font* psf1_font;
	void* mMap;
	uint64_t mMapSize, mMapDescSize;
};
