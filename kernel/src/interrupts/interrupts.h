# pragma once
# include "../utilities/KernelEngine.h"

struct interrupt_frame;
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame);