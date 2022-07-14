#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
	EFI_FILE* LoadedFile;

	// Tells the EFI that we're using the file system 
	// that we are booting from
	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	// Gets our file system
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	// Checks if the directory is NULL
	if (Directory == NULL)
	{
		FileSystem->OpenVolume(FileSystem, &Directory); // Sets the directory to the root
	}

	EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (s != EFI_SUCCESS)
	{
		return NULL; // Just returns NULL if we don't 
					 // end up getting our files
	}
	// Otherwise we're just gonna return our LoadedFile
	return LoadedFile;
}

// Checks if our ELF file is executable, and our header values are correct
int memcmp(const void* aptr, const void* bptr, size_t n)
{
	const unsigned char* a = aptr, *b = bptr;
	for (size_t i = 0 ; i < n ; i++) // scanning two buffers of memory and the size of n
	{
		if (a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
	}
	return 0;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	
	// Sets up the EFI environment for using special commands
	InitializeLib(ImageHandle, SystemTable);
	Print(L"Hello and welcome to the EFI world. \n\r"); // Prints string

	EFI_FILE* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable); /* Our kernel EFI file over here,
					  															 in variables */

	// Checks our LoadFile func is actually working
	if (Kernel == NULL) 
	{
		// If it's not working, we simply 
		// could not load our kernel, unfortunately
		Print(L"Could not load the kernel \n\r");
	}
	else
	{
		Print(L"Kernel loaded Successfully \n\r"); // It's working!
	}

	// Gets the 'elf' header for some information
	// about the file
	Elf32_Ehdr header; // Defining what our header is
	{
		UINTN FileInfoSize;		 // Getting our file info
		EFI_FILE_INFO* FileInfo; // and the size of it
		// Checks if it can't be NULL
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo); // Allocates some fresh memory for us to use
																								 // with the size of FileInfoSize
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo);

		UINTN size = sizeof(header); // Returns the size of our header
		Kernel->Read(Kernel, &size, &header); // Reads the file's content
	}

	// Checks our kernel header against some consts
	if
	(
		memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
		header.e_ident[EI_CLASS] != ELFCLASS64 ||
		header.e_ident[EI_DATA] != ELFDATA2LSB ||
		header.e_type != ET_EXEC ||
		header.e_machine != EM_X86_64 ||
		header.e_version != EV_CURRENT
	)
	{
		Print(L"Bad Kernel Format \r\n");
	}
	else
	{
		Print(L"Kernel header Successfully verified \r\n");
	}

	// Loads the ELF64 program header
	Elf64_Phdr* phdrs;
	{
		
	} 

	return EFI_SUCCESS; // Exit the UEFI application
}
