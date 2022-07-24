#pragma once

// Font file header struct
struct Psf1_Header
{
	unsigned char magic[2]; // Magic bytes
	unsigned char mode; // PSF Mode
	unsigned char charsize; // Character size in bytes
} ;

// Font struct
struct Psf1_Font
{
	Psf1_Header* psf1_header; // Header
	void* glyphBuffer;
};
