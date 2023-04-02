#pragma once
struct PSF2_HEADER{
	unsigned char magic[4];
	unsigned int version;
	unsigned int headersize;
	unsigned int flags;
	unsigned int length;
	unsigned int charsize;
	unsigned int height;
	unsigned int width;
} ;

struct PSF2_FONT{
	PSF2_HEADER* psf2_Header;
	void* glyphBuffer;
} ;