#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

// Creates a struct which is useful for graphics drivers and GOP framebuffer
typedef struct 
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width; // Screen width
	unsigned int Height; // Screen height
	unsigned int PixelPerScanLine; // This operates just like FPS, really useful there
} FrameBuffer;

FrameBuffer Framebuffer; // Creates framebuffer
// Initializes GOP (Graphics Output Protocol)
FrameBuffer* InitializeGOP()
{
	// Finds the GOP GUID
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
	EFI_STATUS status;

	status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void**)&gop); // Fixing our calling conventions so that everything can be call correctly
	Print(L"Checking for Graphics...\n\r");
	// Checks whether the GOP has been located
	if (EFI_ERROR(status))
	{
		Print(L"Unable to Locate GOP, This means you cannot do any renderings.\n\r");
		return NULL; // Prints error message, then halts
	}
	else
	{
		Print(L"GOP Located \n\r");
	}
	Framebuffer.BaseAddress = (void*)gop->Mode->FrameBufferBase;
	Framebuffer.BufferSize = gop->Mode->FrameBufferSize;
	Framebuffer.Width = gop->Mode->Info->HorizontalResolution;
	Framebuffer.Height = gop->Mode->Info->VerticalResolution;
	Framebuffer.PixelPerScanLine = gop->Mode->Info->PixelsPerScanLine;

	return &Framebuffer;
}

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
	Print(L"Initializing daily checks... \n\r");

	EFI_FILE* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable); /* Our kernel EFI file over here, in variables */

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
	Elf64_Ehdr header; // Defining what our header is
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
		Kernel->SetPosition(Kernel, header.e_phoff); // Sets the offset in bytes when we read it
		UINTN size = header.e_phnum * header.e_phentsize;
		SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs); // Allocates memory for the program header
		Kernel->Read(Kernel, &size, phdrs); // Gets all of the bytes of the program header and put it into the struct
	} 

	// Loads the binary information
	// We'll start off with a reference to the first program header
	// and while the program header address is less than all of the program headers, we'll continue
	for
	(
		Elf64_Phdr* phdr = phdrs;
		(char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize;
		phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize)
	)
	{
		switch (phdr->p_type)
		{
			// In case that our type is PT_LOAD we're gonna need to
			// allocate some pages to we could load the program to the memory
			case PT_LOAD:
			{	
				int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000; // Getting and ounding our memsize (p_memsz)
				Elf64_Addr segment = phdr->p_paddr;
				SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

				// Gets the correct offset to read from the kernel
				Kernel->SetPosition(Kernel, phdr->p_offset);
				UINTN size = phdr->p_filesz; // File size
				Kernel->Read(Kernel, &size, (void*)segment);
				break; // Gets out of the loop
			}
		}
	}

	// Sanity checks
	Print(L"Performing sanity checks... \n\r");
	// for (int i = 1; i < 6; i++)
	// {
	Print(L"Kernel Loaded \n\r");
	// }

	// Calling our "int _start function in /../kernel/"
	int (*KernelStart)() = ((__attribute__((sysv_abi)) int (*)() ) header.e_entry);

	// Calling our GOP function
	FrameBuffer* newBuffer = InitializeGOP();

	Print(L"Base: 0x%x\n\rSize: 0x%x\n\rWidth: %d\n\rHeight: %d\n\rPixelPerScanLine: %d\n\r", 
	newBuffer->BaseAddress, 
	newBuffer->BufferSize, 
	newBuffer->Width, 
	newBuffer->Height,
	newBuffer->PixelPerScanLine);

	unsigned int y = 150; // Pixels down the screen we want to pass
	unsigned int BBP = 4; // 4 bytes per pixel

	for (unsigned int x = 0; x < newBuffer->Width / 2 * BBP; x++)
	{
		*(unsigned int*)(x + (y * newBuffer->PixelPerScanLine*BBP)+newBuffer->BaseAddress) = 0xFF00FFFF;
	}

	Print(L"%d\r\n", KernelStart());

	return EFI_SUCCESS; // Exit the UEFI application
}
