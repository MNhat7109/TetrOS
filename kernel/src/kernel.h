#ifndef COLOR_KERNEL_H
#define COLOR_KERNEL_H
typedef unsigned long long size_t;

// Color
enum color
{
    COLOR_RED = 0xffff0000,
    COLOR_BLUE = 0xff0000ff,
    COLOR_YELLOW = 0xffffff00,
};


// PutChar function
// void putChar(FrameBuffer* framebuffer, Psf1_Font* psf1_font, unsigned int color, char chr, unsigned int xOff, unsigned int yOff)
// {
//     unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;
//     char* fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->psf1_header->charsize);
//     for (unsigned long y = yOff; y < yOff+16; y++)
//     {
//         for (unsigned long x = xOff; x < xOff+8; x++)
//         {
//             // Checks if the bit is on or off
//             if ((*fontPtr & (0b10000000 >> (x+xOff))) > 0)
//             {
//                 *(unsigned int*)(pixPtr+x+(y*framebuffer->PixelPerScanLine)) = color;
//             }
//         }
//         fontPtr++;
//     }
// }

#endif