#pragma once
#include "../memory/efiMemory.h"
#include "../util/typedef.h"
#include "../memory/Bitmap.h"
#include "../memory/memory.h"

class PageFrameAllocator {
    public:
    void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize);
    Bitmap PageBitmap;
    void FreePage(void* address);
    void FreePages(void* address, u64 pageCount);
    void LockPage(void* address);
    void LockPages(void* address, u64 pageCount);
    void* RequestPage();
    u64 GetFreeRAM();
    u64 GetUsedRAM();
    u64 GetReservedRAM();


    private:
    void InitBitmap(size_t bitmapSize, void* bufferAddress);
    void ReservePage(void* address);
    void ReservePages(void* address, u64 pageCount);
    void UnreservePage(void* address);
    void UnreservePages(void* address, u64 pageCount);

};

extern PageFrameAllocator GlobalAllocator;