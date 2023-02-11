# include "interrupts.h"
# include "../utilities/panic/panic.h"

__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame)
{
    Panic("Page Fault");
    while(true);
}