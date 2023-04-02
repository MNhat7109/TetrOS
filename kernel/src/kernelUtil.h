#pragma once

#include "util/typedef.h"
#include "BasicRenderer.h"
#include "util/cstr.h"
#include "memory/efiMemory.h"
#include "memory/memory.h"
#include "memory/Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/paging.h"
#include "paging/PageTableManager.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF2_FONT* psf2_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	u64 mMapSize;
	u64 mMapDescSize;
} ;

extern u64 _KernelStart;
extern u64 _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);