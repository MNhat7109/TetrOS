# include "BootInfo.h"
# include "cstr.h"
# include "memory/efiMemory.h"
# include "memory/Bitmap.h"
# include "paging/PFAllocator.h"
# include "paging/PageMapIndexer.h"
# include "paging/paging.h"
# include "paging/PageTableManager.h"

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(bootInfo->Framebuffer, bootInfo->psf1_font); 
	
	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	GlobalAllocator = PFallocator();

	GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);
	uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
	uint64_t kernelPages = (uint64_t)kernelSize / 4096 +1;
	GlobalAllocator.LockPages(&_KernelStart, kernelPages);
 
	PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
	memset(PML4,  0, 0x1000);

	PageTableManager PTManager = PageTableManager(PML4);
	for(uint64_t i = 0; i < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); i += 0x1000)
	{
		PTManager.MapMemory((void*)i, (void*)i);
	}

	uint64_t fbBase = (uint64_t)bootInfo->Framebuffer->BaseAddress;
	uint64_t fbSize = (uint64_t)bootInfo->Framebuffer->BufferSize +0x1000;
	for (uint64_t i = fbBase; i < fbBase+fbSize; i+=4096)
	{
		PTManager.MapMemory((void*)i, (void*)i);
	}

	asm ("mov %0, %%cr3" : : "r" (PML4));
	newRenderer.Print("Page Map created");

    return;
}