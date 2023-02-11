# include "panic.h"
# include "../KernelEngine.h"

void Panic(char* panicMessage)
{
    GlobalRenderer->Clear(0x001F51FF);

    GlobalRenderer->CursorPosition = {0,64};

    GlobalRenderer->Colour = 0;
    GlobalRenderer->Print("Sorry, an error occurred.");

    GlobalRenderer->Next();
    GlobalRenderer->Print(panicMessage);
}