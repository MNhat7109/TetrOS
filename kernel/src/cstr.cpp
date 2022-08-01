# include "cstr.h"

char uIntToString_Output[128];
const char* to_string(uint64_t value)
{
    uint8_t size; // Size of string
    uint64_t sizeTest = value;

    // Calculating size of the string
    while (sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while (value / 10 > 0)
    {
        uint8_t rem = value % 10;
        value /= 10;
        uIntToString_Output[size - index] = rem + '0';
        index++;
    }
    uint8_t rem = value % 10;
    uIntToString_Output[size-index] = rem + '0';
    uIntToString_Output[size+1] = 0;
    return uIntToString_Output;
}

char IntToString_Output[128]; // Buffer
const char* to_string(int64_t value)
{
    // Checks if value is negative
    uint8_t isNegative = 0;
    
    if (value < 0)
    {
        isNegative = 1;
        value *= -1;
        IntToString_Output[0] = '-';
    }

    uint8_t size; // Size of string
    uint64_t sizeTest = value;

    // Calculating size of the string
    while (sizeTest / 10 > 0)
    {
        sizeTest /= 10;
        size++;
    }

    uint8_t index = 0;
    while (value / 10 > 0)
    {
        uint8_t rem = value % 10;
        value /= 10;
        IntToString_Output[isNegative+size - index] = rem + '0';
        index++;
    }
    uint8_t rem = value % 10;
    IntToString_Output[isNegative+size-index] = rem + '0';
    IntToString_Output[isNegative+size+1] = 0;
    return IntToString_Output;
}

char DoubleToString_Output[128];
const char* to_string(double value, uint8_t decimalPlaces)
{
    if (decimalPlaces > 20) decimalPlaces = 20;

    char* intPtr = (char*)to_string((int64_t)value); // Signed integer-casted version of to_string()
    char* doublePtr = DoubleToString_Output; // Buffer

    if (value < 0) value *=-1; // If the value is less than 0 then we should put a '-' sign before it
    
    // While the intPtr value is not 0 then copy doublePtr to it
    while (*intPtr != 0) *doublePtr++ = *intPtr++;

    *doublePtr = '.'; // Put a floating point
    doublePtr++;

    double newValue = value - (int)value; // Chopping out the whole number for the decimal parts

    for (uint8_t i = 0; i < decimalPlaces; i++) // While i is less than decimal places
    {
        newValue *= 10; // Multiplies the decimal parts by 10
        *doublePtr = (int)newValue + '0';
        newValue -= (int)newValue;
        doublePtr++; // Increments the buffer
    }

    *doublePtr = 0; // Free up memory used by the pointer
    return DoubleToString_Output; // Return the buffer
}

char hexToString_Output64[128];
const char* to_hstring(uint64_t value)
{
    uint64_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8*2-1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr+i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToString_Output64[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToString_Output64[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToString_Output64[size + 1] = 0;
    return hexToString_Output64;
}

char hexToString_Output32[128];
const char* to_hstring(uint32_t value)
{
    uint32_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8*2-1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr+i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToString_Output32[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToString_Output32[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToString_Output32[size + 1] = 0;
    return hexToString_Output32;
}

char hexToString_Output16[128];
const char* to_hstring(uint16_t value)
{
    uint16_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8*2-1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr+i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToString_Output16[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToString_Output16[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToString_Output16[size + 1] = 0;
    return hexToString_Output16;
}

char hexToString_Output8[128];
const char* to_hstring(uint8_t value)
{
    uint8_t* valPtr = &value;
    uint8_t* ptr;
    uint8_t tmp;
    uint8_t size = 8*2-1;
    
    for (uint8_t i = 0; i < size; i++)
    {
        ptr = ((uint8_t*)valPtr+i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToString_Output8[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : '0');
        tmp = ((*ptr & 0x0F));
        hexToString_Output8[size - (i * 2)] = tmp + (tmp > 9 ? 55 : '0');
    }
    
    hexToString_Output8[size + 1] = 0;
    return hexToString_Output8;
}