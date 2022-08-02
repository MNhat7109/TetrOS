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