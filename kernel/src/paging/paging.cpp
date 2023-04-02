#include "paging.h"

void PageDirectoryEntry::SetFlag(PT_Flag flag, bool enabled){
    u64 bitSelector = (u64)1 << flag;
    Value &= ~bitSelector;
    if (enabled){
        Value |= bitSelector;
    }
}

bool PageDirectoryEntry::GetFlag(PT_Flag flag){
    u64 bitSelector = (u64)1 << flag;
    return Value & bitSelector > 0 ? true : false;
}

u64 PageDirectoryEntry::GetAddress(){
    return (Value & 0x000ffffffffff000) >> 12;
}

void PageDirectoryEntry::SetAddress(u64 address){
    address &= 0x000000ffffffffff;
    Value &= 0xfff0000000000fff;
    Value |= (address << 12);
}