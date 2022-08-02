# include "efiMemory.h"

const char* efiMemoryTypeStrings[]
{
    "EfiReservedMemoryType",

    "EfiLoaderCode",
    "EfiLoaderData",
    
    "EfiBootServicesCode",
    "EfiBootServicesData",
    
    "EfiRuntimeServicesCode",
    "EfiRuntimeServicesData",
    
    "EfiConventionalMemory",
    "EfiUnusableMemory",
    
    "EfiACPIReclaimMemory",
    "EfiACPIMemoryNVS",
    
    "EfiMemoryMappedIO",
    "EfiMemoryMappedIOPortSpace",
    "EfiPalCode",
};