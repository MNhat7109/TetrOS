#pragma once

#include <stdint.h>
#include <stddef.h>

struct FrameBuffer
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width; // Screen width
	unsigned int Height; // Screen height
	unsigned int PixelPerScanLine; // This operates just like FPS, really useful there
} ;
