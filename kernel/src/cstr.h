# pragma once

// Include
# include <stdint.h>
# include <stddef.h>

const char* to_string(uint64_t value);
const char* to_string(int64_t value);
const char* to_string(double value, uint8_t decimalPlace);