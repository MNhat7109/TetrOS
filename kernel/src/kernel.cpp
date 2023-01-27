# include "BootInfo.h"
# include "cstr.h"
# include "memory/efiMemory.h"
# include "memory/Bitmap.h"
# include "paging/PFAllocator.h"
# include "paging/PageMapIndexer.h"

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(bootInfo->Framebuffer, bootInfo->psf1_font); 
	
	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	PFallocator newAlloc;

	newAlloc.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);
	uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
	uint64_t kernelPages = (uint64_t)kernelSize / 4096 +1;
	newAlloc.LockPages(&_KernelStart, kernelPages);

	PageMapIndexer pageIndexer = PageMapIndexer(0x1000);
	

    return;
}