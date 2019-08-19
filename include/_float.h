#ifndef __FLOAT_
#define __FLOAT_

#ifdef _TRACE_FLOAT_OPERATIONS_
#include "pindefs.h"
#define __TRACE(x) TRACE(X)
#define __TRACELN(x) TRACELN(x)
#else
#define __TRACE(x)
#define __TRACELN(x)
#endif

#include <stdint.h>
#include <stddef.h>

#define __FLOAT_DEFINE_CMP_OPS

#define __FLOAT_PT_INT 100
#define __FLOAT_PT_FLOAT 100.0f
#define __FLOAT_PT_DOUBLE 100.0

class _float
{
	int64_t data;

protected:
	uint64_t getData() const;

public:
	_float();
	_float(int i);
	_float(unsigned int i);
	_float(float f);
	_float(double d);
	_float(uint32_t i);

	_float &operator+=(const _float &f);
	_float &operator+=(int f);
	_float &operator-=(const _float &f);
	_float &operator*=(float);
	_float &operator*=(const _float &f);
	_float &operator*=(int);
	_float &operator/=(float);
	_float &operator/=(int);
	_float &operator/=(const _float &f);

#ifdef __FLOAT_DEFINE_CMP_OPS
	bool operator>(const _float &f) const;
	bool operator>(float val) const;
	bool operator>(double val) const;
	bool operator>(int16_t val) const;
	bool operator>(uint16_t val) const;
	bool operator>(int val) const;

	bool operator>=(const _float &f) const;
	bool operator>=(float val) const;
	bool operator>=(double val) const;
	bool operator>=(int16_t val) const;
	bool operator>=(uint16_t val) const;
	bool operator>=(int val) const;

	bool operator<(const _float &f) const;
	bool operator<(float val) const;
	bool operator<(double val) const;
	bool operator<(int16_t val) const;
	bool operator<(uint16_t val) const;
	bool operator<(int val) const;

	bool operator<=(const _float &f) const;
	bool operator<=(float val) const;
	bool operator<=(double val) const;
	bool operator<=(int16_t val) const;
	bool operator<=(uint16_t val) const;
	bool operator<=(int val) const;

	bool operator==(const _float &f) const;
	bool operator==(float val) const;
	bool operator==(double val) const;
	bool operator==(int16_t val) const;
	bool operator==(uint16_t val) const;
	bool operator==(int val) const;

	bool operator!=(const _float &f) const;
	bool operator!=(float val) const;
	bool operator!=(double val) const;
	bool operator!=(int16_t val) const;
	bool operator!=(uint16_t val) const;
	bool operator!=(int val) const;
#endif

	_float &operator=(const _float &f);
	_float &operator=(float f);
	_float &operator=(double d);
	_float &operator=(int f);
	_float &operator=(unsigned int f);
	_float &operator=(uint32_t);

	operator int() const;
	operator unsigned int() const;
	operator float() const;
	operator double() const;
	operator uint32_t() const;
	operator uint8_t() const;

	void print(char *str) const;
	void print(char *str, uint8_t digit_before_comma) const;

	static _float direct(int64_t val);
	static size_t serialize(uint8_t *buffer, size_t len, const _float *val);
	static size_t deserialize(const uint8_t *buffer, size_t len, _float *val);
};

#endif
