#pragma once

#include "_float.h"

namespace rkp
{

_float u_adc_direct(uint32_t adc);

_float set_u_direct(uint32_t u);
_float set_u_double_rounded(uint32_t u);

namespace r10k
{

_float set_i_direct(uint32_t up, uint32_t u);
_float set_i_double_exact(uint32_t up, uint32_t u);
_float set_i_double_rounded(uint32_t up, uint32_t u);

} // namespace r10k

_float is_u_direct(uint32_t is);
_float is_u_double_rounded(uint32_t is);

_float is_i_direct(uint32_t is);
_float is_i_double_rounded(uint32_t is);

uint32_t stab_ana_read(uint8_t pin);
uint32_t stab_ana_read(uint8_t pin, uint32_t valCount);
} // namespace rkp
