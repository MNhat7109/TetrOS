# include "memory.h"

uint64_t GetMemorySize(efiMemoryDescriptor* mMap, uint64_t mMapEntries, uint64_t mMapDescSize)
{
    static uint64_t memorySizeBytes = 0;
    if (memorySizeBytes > 0) return memorySizeBytes;
    for (int i = 0; i < mMapDescSize; i++)
    {
        efiMemoryDescriptor* desc = (efiMemoryDescriptor*)((uint64_t)mMap+i*mMapDescSize);
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;
}

void memset(void* start, uint8_t value, uint64_t num)
{
    for (uint64_t i=0; i < num; i++)
    {
        *(uint8_t*)((uint64_t)start +i) = value;
    }
}