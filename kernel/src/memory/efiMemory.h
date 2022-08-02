# pragma once

# include <stdint.h>

struct efiMemoryDescriptor
{
    uint32_t type; // Type of memory
    void* physAddr; // Physical address
    void* virtAddr; // Virtual address
    uint64_t numPages, attrib;
};

 // Declare types
 extern const char* efiMemoryTypeStrings[];