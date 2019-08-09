#pragma once

#include <stddef.h>
#include <stdint.h>
#include <Arduino.h>

namespace rkp
{

void clearStr(char *str, size_t len);

void printFloat(char *str, int32_t length, int32_t iNum);

void printInt(char *str, int32_t length, int32_t iNum);

size_t dynIntToStr(char* str, size_t lenMax, int32_t iNum);

void cpystr(char *dest, const char *src);

uint32_t stab_ana_read(int32_t pin);

}; // namespace rkp