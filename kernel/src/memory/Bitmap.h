# pragma once

# include <stddef.h>
# include <stdint.h>

class Bitmap
{
    public:
    size_t Size; // size of the buffer
    uint8_t* Buffer; // buffer to store the data
    bool operator[](uint64_t index);
    void Set(uint64_t index, bool value);
};