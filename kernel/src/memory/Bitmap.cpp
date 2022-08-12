# include "Bitmap.h"

bool Bitmap::operator[](uint64_t index)
{
    uint64_t byteIndex = index / 8; // Get the byte index
    uint8_t bitIndex = index % 8; // Get the bit index, which was the remainder of byteIndex

}