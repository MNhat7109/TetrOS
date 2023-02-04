# pragma once
# include <stdint.h>

# define IDT_TA_InterruptGate 0b10001110 // IDT interrupt gate
# define IDT_TA_CallGate 0b10001100      // IDT call gate
# define IDT_TA_TrapGate 0b10001111      // IDT trap gate

struct IDTDescEntry
{
    uint16_t offset0;
    uint16_t selector;
    uint8_t ist; //interrupt stack table
    uint8_t type_attr; //type attribute
    uint16_t offset1;
    uint32_t offset2;
    uint32_t ignore;
    void SetOffset(uint64_t offset);
    uint64_t GetOffset();
};

struct IDTR
{
    uint16_t Limit;
    uint64_t Offset;
} __attribute__((packed));

