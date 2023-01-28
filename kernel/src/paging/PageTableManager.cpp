# include "PageTableManager.h"
# include "PageMapIndexer.h"
# include "PFAllocator.h"
# include <stdint.h>
# include "../memory/memory.h"

PageTableManager::PageTableManager(PageTable* PML4Addr)
{
    this->PML4 = PML4Addr;
    
}

void PageTableManager::MapMemory(void* virtualMemory, void* physicalMemory)
{
    PageMapIndexer indexer = PageMapIndexer((uint64_t) virtualMemory);
    PageDirectoryEntry PDE;

    PDE = PML4->entries[indexer.PDP_i];
    PageTable* PDP;
    if (!PDE.Present)
    {
        PDP = (PageTable*)GlobalAllocator.RequestPage();
        memset(PDP, 0, 0x1000);
        PDE.address = (uint64_t)PDP >>12;
        PDE.Present = true;
        PDE.RW = true;
        PML4->entries[indexer.PDP_i] = PDE;
    }
    else
    {
        PDP = (PageTable*)((uint64_t)PDE.address << 12);
    }
    
    PDE = PDP->entries[indexer.PD_i];
    PageTable* PD;
    if (!PDE.Present)
    {
        PD = (PageTable*)GlobalAllocator.RequestPage();
        memset(PD, 0, 0x1000);
        PDE.address = (uint64_t)PD >> 12;
        PDE.Present = true;
        PDE.RW = true;
        PDP->entries[indexer.PD_i] = PDE;
    }
    else
    {
        PD = (PageTable*)((uint64_t)PDE.address << 12);
    }

    PDE = PD->entries[indexer.PT_i];
    PageTable* PT;
    if (!PDE.Present)
    {
        PT = (PageTable*)GlobalAllocator.RequestPage();
        memset(PT, 0, 0x1000);
        PDE.address = (uint64_t)PT >> 12;
        PDE.Present = true;
        PDE.RW = true;
        PD->entries[indexer.PT_i] = PDE;
    }
    else
    {
        PT = (PageTable*)((uint64_t)PDE.address << 12);
    }

    PDE = PT->entries[indexer.P_i];
    PDE.address = (uint64_t)physicalMemory >> 12;
    PDE.Present = true;
    PDE.RW = true;
    PT->entries[indexer.P_i] = PDE;

}