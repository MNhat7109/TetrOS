#pragma once
# include "typedef.h"

const char* to_string(u64 value);
const char* to_string(i64 value);
const char* to_hstring(u64 value);
const char* to_hstring(u32 value);
const char* to_hstring(u16 value);
const char* to_hstring(u8 value);
const char* to_string(double value, u8 decimalPlaces);
const char* to_string(double value);
