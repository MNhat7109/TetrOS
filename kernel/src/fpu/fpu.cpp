# include "fpu.h"

void InitFPU()
{
    size_t t;

    asm ("clts");
    asm ("mov %%cr0, %0":"=r"(t));
    t &= ~(1 << 2);
    t |= (1 << 1);
    asm ("mov %0, %%cr0"::"r"(t));
    asm ("mov %%cr4, %0":"=r"(t));
    t |= (1 << 9);
    asm ("mov %0, %%cr4"::"r"(t));
    asm ("fninit");
}