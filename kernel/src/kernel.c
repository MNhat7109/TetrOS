# include "kernel.h"



void _start(FrameBuffer* framebuffer, Psf1_Font* psf1_font)
{
    // unsigned int y = 0.5; // Pixels down the screen we want to pass
	// unsigned int BBP = 4; // 4 bytes per pixel

	// for (y; y < framebuffer->Height/2*BBP; y+=0.5+BBP)
	// {
	// 	for (unsigned int x = 0; x < framebuffer->Width  * BBP; x+=BBP)
	// 	{
	// 		*(unsigned int*)(x + (y * framebuffer->PixelPerScanLine*BBP)+framebuffer->BaseAddress) = COLOR_BLUE; // green
	// 	}
	// }
	Position.X = 0;
	Position.Y = 16;
	Print(framebuffer, psf1_font, COLOR_WHITE, "It's Tetris time");
    return;
}