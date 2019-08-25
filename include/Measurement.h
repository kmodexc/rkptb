#pragma once

#include "Arduino.h"
#include "PhysicalValue.h"

namespace rkp
{

PhysicalValue u_adc_direct(uint32_t adc);

PhysicalValue set_u_direct(uint32_t u);
PhysicalValue set_u_double_rounded(uint32_t u);

namespace r10k
{

PhysicalValue set_i_direct(uint32_t up, uint32_t u);
PhysicalValue set_i_double_exact(uint32_t up, uint32_t u);
PhysicalValue set_i_double_rounded(uint32_t up, uint32_t u);

} // namespace r10k

PhysicalValue is_u_direct(uint32_t is);
PhysicalValue is_u_double_rounded(uint32_t is);

PhysicalValue is_i_direct(uint32_t is);
PhysicalValue is_i_double_rounded(uint32_t is);

uint32_t stab_ana_read(uint8_t pin);
uint32_t stab_ana_read(uint8_t pin, uint32_t valCount);
} // namespace rkp
