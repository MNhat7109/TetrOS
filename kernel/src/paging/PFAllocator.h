# pragma once
# include "../memory/efiMemory.h"
# include <stdint.h>
# include "../memory/Bitmap.h"
# include "../memory/memory.h"

class PFallocator
{
    public:
    void ReadEFIMemoryMap(efiMemoryDescriptor* mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap pageBitmap;
    void FreePage(void* address);
    void LockPage(void* address);
    void FreePages(void* address, uint64_t pageCount);
    void LockPages(void* address, uint64_t pageCount);
    void* RequestPage();
    uint64_t GetFreeMem();
    uint64_t GetUsedMem();
    uint64_t GetReservedMem();
    

    private:
    void InitBitmap(size_t bitmapSize, void* bufferAddress);
    void ReservePage(void* address);
    void ReleasePage(void* address);
    void ReservePages(void* address, uint64_t pageCount);
    void ReleasePages(void* address, uint64_t pageCount);

};