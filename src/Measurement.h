#ifndef _MEASUREMENT_H_
#define _MEASUREMENT_H_

#include "_float.h"

class Measurement{
  public:
static _float set_u_direct(int32_t pu);
static _float set_i_direct(int32_t pup, int32_t pu);
static _float is_u_direct(int32_t pis);
static _float is_i_direct(int32_t pis);
};

#endif
