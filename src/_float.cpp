#ifndef __FLOAT_CPP_
#define __FLOAT_CPP_
#include "_float.h"

_float::_float()
{
  data = 0;
}
_float::_float(int32_t i)
{
  this->operator=(i);
}
_float::_float(uint32_t i)
{
  this->operator=(i);
}
_float::_float(float f)
{
  this->operator=(f);
}
_float& _float::operator+=(_float& f)
{
  data += f.data;
  return *this;
}
_float& _float::operator+=(int f)
{
  data += f * 100;
  return *this;
}
_float& _float::operator-=(_float& f)
{
  data -= f.data;
  return *this;
}
_float& _float::operator*=(float f)
{
  data *= f;
  return *this;
}
_float& _float::operator*=(int32_t f)
{
  data *= f;
  return *this;
}
_float& _float::operator*=(int f)
{
  data *= f;
  return *this;
}
_float& _float::operator/=(float f)
{
  data /= f;
  return *this;
}
_float& _float::operator/=(int32_t f)
{
  data /= f;
  return *this;
}
_float& _float::operator/=(int f)
{
  data /= f;
  return *this;
}
_float& _float::operator=(_float &f)
{
  data = f.data;
  return *this;
}
_float& _float::operator=(float f)
{
  data = f * 100.0;
  return *this;
}
_float& _float::operator=(int32_t i)
{
  data = i;
  data *= 100;
  return *this;
}
_float& _float::operator=(uint32_t i)
{
  if (i > 0x7FFFFFFF) {
    i = 0x7FFFFFFF;
  }
  data = (int32_t)i;
  data *= 100;
  return *this;
}
void _float::print(char* str)
{
  if (str) {
    int32_t iNum = 0;
    if (data >= 0) iNum = data;
    //str[4] = (iNum % 10) + 48;
    iNum /= 10;
    str[3] = (iNum % 10) + 48;
    iNum /= 10;
    str[2] = '.';
    str[1] = (iNum % 10) + 48;
    iNum /= 10;
    str[0] = (iNum % 10) + 48;
  }
}

long _float::getData()
{
  return data;
}

_float _float::direct(long val) {
  _float f;
  f.data = val;
  return f;
}

#endif