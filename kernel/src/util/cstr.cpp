#include "cstr.h"

char uintTo_StringOutput[128];
const char* to_string(u64 value){
    u8 size;
    u64 sizeTest = value;
    while (sizeTest / 10 > 0){
        sizeTest /= 10;
        size++;
    }

    u8 index = 0;
    while(value / 10 > 0){
        u8 remainder = value % 10;
        value /= 10;
        uintTo_StringOutput[size - index] = remainder + '0';
        index++;
    }
    u8 remainder = value % 10;
    uintTo_StringOutput[size - index] = remainder + '0';
    uintTo_StringOutput[size + 1] = 0; 
    return uintTo_StringOutput;
}

char hexTo_StringOutput[128];
const char* to_hstring(u64 value){
    u64* valPtr = &value;
    u8* ptr;
    u8 tmp;
    u8 size = 8 * 2 - 1;
    for (u8 i = 0; i < size; i++){
        ptr = ((u8*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexTo_StringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexTo_StringOutput[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexTo_StringOutput[size + 1] = 0;
    return hexTo_StringOutput;
}

char hexTo_StringOutput32[128];
const char* to_hstring(u32 value){
    u32* valPtr = &value;
    u8* ptr;
    u8 tmp;
    u8 size = 4 * 2 - 1;
    for (u8 i = 0; i < size; i++){
        ptr = ((u8*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexTo_StringOutput32[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexTo_StringOutput32[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexTo_StringOutput32[size + 1] = 0;
    return hexTo_StringOutput32;
}

char hexTo_StringOutput16[128];
const char* to_hstring(u16 value){
    u16* valPtr = &value;
    u8* ptr;
    u8 tmp;
    u8 size = 2 * 2 - 1;
    for (u8 i = 0; i < size; i++){
        ptr = ((u8*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexTo_StringOutput16[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexTo_StringOutput16[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexTo_StringOutput16[size + 1] = 0;
    return hexTo_StringOutput16;
}

char hexTo_StringOutput8[128];
const char* to_hstring(u8 value){
    u8* valPtr = &value;
    u8* ptr;
    u8 tmp;
    u8 size = 1 * 2 - 1;
    for (u8 i = 0; i < size; i++){
        ptr = ((u8*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexTo_StringOutput8[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexTo_StringOutput8[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    hexTo_StringOutput8[size + 1] = 0;
    return hexTo_StringOutput8;
}

char intTo_StringOutput[128];
const char* to_string(i64 value){
    u8 isNegative = 0;

    if (value < 0){
        isNegative = 1;
        value *= -1;
        intTo_StringOutput[0] = '-';
    }

    u8 size;
    u64 sizeTest = value;
    while (sizeTest / 10 > 0){
        sizeTest /= 10;
        size++;
    }

    u8 index = 0;
    while(value / 10 > 0){
        u8 remainder = value % 10;
        value /= 10;
        intTo_StringOutput[isNegative + size - index] = remainder + '0';
        index++;
    }
    u8 remainder = value % 10;
    intTo_StringOutput[isNegative + size - index] = remainder + '0';
    intTo_StringOutput[isNegative + size + 1] = 0; 
    return intTo_StringOutput;
}

char doubleTo_StringOutput[128];
const char* to_string(double value, u8 decimalPlaces){
    if (decimalPlaces > 20) decimalPlaces = 20;

    char* intPtr = (char*)to_string((i64)value);
    char* doublePtr = doubleTo_StringOutput;

    if (value < 0){
        value *= -1;
    }

    while(*intPtr != 0){
        *doublePtr = *intPtr;
        intPtr++;
        doublePtr++;
    }

    *doublePtr = '.';
    doublePtr++;

    double newValue = value - (int)value;

    for (u8 i = 0; i < decimalPlaces; i++){
        newValue *= 10;
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++;
    }

    *doublePtr = 0;
    return doubleTo_StringOutput;
}

const char* to_string(double value){
    return to_string(value, 2);
}
