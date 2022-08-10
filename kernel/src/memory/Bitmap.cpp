# include "Bitmap.h"

bool Bitmap::operator[](uint64_t index)
{
    // Get the bits and bytes
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;

    if ((Buffer[byteIndex] & bitIndexer) > 0) return true;

    return false;
}

void Bitmap::Set(uint64_t index, bool value)
{
    // Get the bits and bytes
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;

    Buffer[byteIndex] &= ~bitIndexer;
}