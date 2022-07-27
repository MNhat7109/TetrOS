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
const char* to_string(double value, uint8_t decimalPlace)
{
    char* intPtr = (char*)to_string((int64_t)value);
    char* doublePtr = DoubleToString_Output;

    if (value < 0) value *=1;
    
}