#include "BasicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF2_FONT* psf2_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF2_Font = psf2_Font;
    Colour = COLOR(255,255,255);
    CursorPosition = {0, 0};
}

void BasicRenderer::Clear(uint32_t colour){
    uint64_t fbBase = (uint64_t)TargetFramebuffer->BaseAddress;
    uint64_t bytesPerScanline = TargetFramebuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = TargetFramebuffer->Height;
    uint64_t fbSize = TargetFramebuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline ++){
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr ++){
            *pixPtr = colour;
        }
    }
}

void BasicRenderer::Next(){
    CursorPosition.X = 0;
    CursorPosition.Y += 20;
}

void BasicRenderer::Print(const char* str)
{
    
    char* chr = (char*)str;
    while(*chr != 0){
        PutChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X+=10;
        if(CursorPosition.X + 10 > TargetFramebuffer->Width)
        {
            CursorPosition.X = 0;
            CursorPosition.Y += 20;
        }
        chr++;
    }
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    if (chr == '\n')
    {
        CursorPosition.X = -(PSF2_Font->psf2_Header->width);
        CursorPosition.Y += PSF2_Font->psf2_Header->height;
    }
    else if (chr == '\r')
    {
        GlobalRenderer->Clear(0xff000000);
        CursorPosition.X = -(PSF2_Font->psf2_Header->width);
        CursorPosition.Y += PSF2_Font->psf2_Header->height;
    }
    else
    {   
        unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
        char* fontPtr = (char*)PSF2_Font->glyphBuffer + (chr * PSF2_Font->psf2_Header->charsize);
        int BytesperScanLine = (PSF2_Font->psf2_Header->width+7)/8;
        for (unsigned long y = yOff; y < yOff + PSF2_Font->psf2_Header->height; y++){
            for (unsigned long x = xOff; x < xOff+PSF2_Font->psf2_Header->width; x++){
                if ((*fontPtr & (0b1000000000 >> (x - xOff))) > 0){
                        *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
                    }

            }
            fontPtr+=BytesperScanLine;
        }
    }
}