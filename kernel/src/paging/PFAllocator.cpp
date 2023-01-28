#include "PFAllocator.h"

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool init = false;
PFallocator GlobalAllocator;

void PFallocator::InitBitmap(size_t bitmapSize, void* bufferAddress)
{
    pageBitmap.size = bitmapSize;
    pageBitmap.Buffer = (uint8_t*)bufferAddress;
    for (int i =0; i < bitmapSize; i++)
    {
        *(uint8_t*)(pageBitmap.Buffer + i) = 0;
    }
}

void PFallocator::FreePage(void* address)
{
    uint64_t index = (uint64_t)address / 4096;
    if (pageBitmap[index] == false) return;
    pageBitmap.Set(index, false);
    freeMemory += 4096;
    usedMemory -= 4096;
}

void PFallocator::LockPage(void* address)
{
    uint64_t index = (uint64_t)address / 4096;
    if (pageBitmap[index] == true) return;
    pageBitmap.Set(index, true);
    freeMemory -= 4096;
    usedMemory += 4096;
}

void PFallocator::FreePages(void *address, uint64_t pageCount)
{
    for (int i = 0; i < pageCount; i++)
    {
        FreePage((void*)((uint64_t)address + (i*4096)));
    }
}
void PFallocator::LockPages(void *address, uint64_t pageCount)
{
    for (int i = 0; i < pageCount; i++)
    {
        LockPage((void*)((uint64_t)address + (i*4096)));
    }
}
void PFallocator::ReservePages(void *address, uint64_t pageCount)
{
    for (int i = 0; i < pageCount; i++)
    {
        ReservePage((void*)((uint64_t)address + (i*4096)));
    }
}
void PFallocator::ReleasePages(void *address, uint64_t pageCount)
{
    for (int i = 0; i < pageCount; i++)
    {
        ReleasePage((void*)((uint64_t)address + (i*4096)));
    }
}

void PFallocator::ReservePage(void* address)
{
    uint64_t index = (uint64_t)address / 4096;
    if (pageBitmap[index] == true) return;
    pageBitmap.Set(index, true);
    freeMemory -= 4096;
    reservedMemory += 4096;
}

void PFallocator::ReleasePage(void* address)
{
    uint64_t index = (uint64_t)address / 4096;
    if (pageBitmap[index] == false) return;
    pageBitmap.Set(index, false);
    freeMemory += 4096;
    reservedMemory -= 4096;
}

void PFallocator::ReadEFIMemoryMap(efiMemoryDescriptor* mMap, size_t mMapSize, size_t mMapDescSize)
{
    PFallocator pfa;
    if (init) return;
    init = true;
    uint64_t mMapEntries = mMapSize / mMapDescSize;
    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for (int i = 0; i < mMapEntries; i++) 
    {
        efiMemoryDescriptor* desc = (efiMemoryDescriptor*)((uint64_t)mMap + (i*mMapDescSize));
        if (desc->type == 7)
        {
            if (desc->numPages * 4096 > largestFreeMemSegSize)
            {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages *4096;
            }
        }
    }

    uint64_t memSize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMemory = memSize;
    uint64_t bitmapSize = memSize / 4096 / 8 +1;

    InitBitmap(bitmapSize, largestFreeMemSeg);
    LockPages(&pageBitmap.Buffer, pageBitmap.size / 4096+1);

    for (int i = 0; i < mMapEntries; i++) 
    {
        efiMemoryDescriptor* desc = (efiMemoryDescriptor*)((uint64_t)mMap + (i*mMapDescSize));
        if (desc->type != 7)
        {
            ReservePages(desc->physAddr, desc->numPages);
        }
    }
}

uint64_t PFallocator::GetFreeMem() {return freeMemory;}
uint64_t PFallocator::GetUsedMem() {return usedMemory;}
uint64_t PFallocator::GetReservedMem() {return reservedMemory;}

void* PFallocator::RequestPage()
{
    for (uint64_t index=0; index < pageBitmap.size*8; index++)
    {
        if (pageBitmap[index] == true) continue;
        LockPage((void*)(index*4096));
        return (void*)(index*4096);
    }

    return NULL;
}