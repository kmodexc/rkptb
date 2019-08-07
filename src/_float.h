#ifndef __FLOAT_
#define __FLOAT_

#include "Arduino.h"

class _float{
	//public:
		int64_t data;
	public:
		_float();
		_float(int32_t i);
    _float(uint32_t i);
		_float(float f);
		_float& operator+=(_float& f);
    _float& operator+=(int f);
		_float& operator-=(_float& f);
		_float& operator*=(float);
    _float& operator*=(int32_t);
    _float& operator*=(int);
		_float& operator/=(float);
    _float& operator/=(int32_t);
    _float& operator/=(int);
		_float& operator=(_float& f);
		_float& operator=(float f);
		_float& operator=(int32_t f);
    _float& operator=(uint32_t f);

		void print(char* str);

		long getData();

		static _float direct(long val);

};

#endif
