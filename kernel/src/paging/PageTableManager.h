# pragma once
# include "paging.h"

class PageTableManager
{
public:
    PageTableManager(PageTable* PML4Addr);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory);
};
