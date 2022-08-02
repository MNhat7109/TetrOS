# include "BootInfo.h"
# include "cstr.h"
# include "memory/efiMemory.h"

extern "C" void _start(BootInfo* bootInfo)
{
	// Class declarations
	KernelEngine newRenderer = KernelEngine(bootInfo->Framebuffer, bootInfo->psf1_font); 
	
	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

	newRenderer.Print(to_string(GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize)));
	// for (int i =0 ; i < mMapEntries ; i++)
	// {
	// 	efiMemoryDescriptor* desc = (efiMemoryDescriptor*)((uint64_t)bootInfo->mMap + (i*bootInfo->mMapDescSize));
	// 	newRenderer.Position = {0, newRenderer.Position.Y+16}; // Set Cursor Position
	// 	newRenderer.Print(efiMemoryTypeStrings[desc->type]);
	// 	newRenderer.Color = COLOR_YELLOW; // Set Color
	// 	newRenderer.Print(" ");
	// 	newRenderer.Print(to_string(desc->numPages * 4));
	// 	newRenderer.Print(" KB");
	// 	newRenderer.Color = COLOR_WHITE;
	// }

    return;
}