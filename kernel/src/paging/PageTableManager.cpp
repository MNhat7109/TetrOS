# include "PageTableManager.h"
# include "PageMapIndexer.h"
# include "PFAllocator.h"
# include <stdint.h>

PageTableManager::PageTableManager(PageTable* PML4Addr)
{
    this->PML4 = PML4Addr;
    
}