#ifndef __FLOAT_CPP_
#define __FLOAT_CPP_
#include "_float.h"

_float::_float()
{
	data = 0;
}
_float::_float(int i)
{
	this->operator=(i);
}
_float::_float(unsigned int i)
{
	this->operator=(i);
}
_float::_float(float f)
{
	this->operator=(f);
}
_float::_float(double d)
{
	this->operator=(d);
}
_float::_float(uint32_t i)
{
	this->operator=(i);
}
_float &_float::operator+=(_float &f)
{
	data += f.data;
	return *this;
}
_float &_float::operator+=(int f)
{
	data += f * __FLOAT_PT_INT;
	return *this;
}
_float &_float::operator-=(_float &f)
{
	data -= f.data;
	return *this;
}
_float &_float::operator*=(float f)
{
	data *= f;
	return *this;
}
_float &_float::operator*=(int f)
{
	data *= f;
	return *this;
}
_float &_float::operator/=(float f)
{
	data /= f;
	return *this;
}
_float &_float::operator/=(int f)
{
	data /= f;
	return *this;
}
#ifdef __FLOAT_DEFINE_CMP_OPS
bool _float::operator>(const _float &f) const
{
	return data > f.data;
}
bool _float::operator>(float val) const
{
	return data > (int64_t)(val * __FLOAT_PT_FLOAT);
}
bool _float::operator>(double val) const
{
	return data > (int64_t)(val * __FLOAT_PT_DOUBLE);
}
bool _float::operator>(int16_t val) const
{
	return data > (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator>(uint16_t val) const
{
	return data > (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator>(int val) const
{
	return data > (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator>=(const _float &f) const
{
	return data >= f.data;
}
bool _float::operator>=(float val) const
{
	return data >= (int64_t)val * __FLOAT_PT_FLOAT;
}
bool _float::operator>=(double val) const
{
	return data >= (int64_t)val * __FLOAT_PT_DOUBLE;
}
bool _float::operator>=(int16_t val) const
{
	return data >= (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator>=(uint16_t val) const
{
	return data >= (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator>=(int val) const
{
	return data >= (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator<(const _float &f) const
{
	return data < f.data;
}
bool _float::operator<(float val) const
{
	return data < (int64_t)(val * __FLOAT_PT_FLOAT);
}
bool _float::operator<(double val) const
{
	return data < (int64_t)(val * __FLOAT_PT_DOUBLE);
}
bool _float::operator<(int16_t val) const
{
	return data < (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator<(uint16_t val) const
{
	return data < (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator<(int val) const
{
	return data < (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator<=(const _float &f) const
{
	return data <= f.data;
}
bool _float::operator<=(float val) const
{
	return data <= (int64_t)(val * __FLOAT_PT_FLOAT);
}
bool _float::operator<=(double val) const
{
	return data <= (int64_t)(val * __FLOAT_PT_DOUBLE);
}
bool _float::operator<=(int16_t val) const
{
	return data <= (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator<=(uint16_t val) const
{
	return data <= (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator<=(int val) const
{
	return data <= (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator==(const _float &f) const
{
	return data == f.data;
}
bool _float::operator==(float val) const
{
	return data == (int64_t)(val * __FLOAT_PT_FLOAT);
}
bool _float::operator==(double val) const
{
	return data == (int64_t)(val * __FLOAT_PT_DOUBLE);
}
bool _float::operator==(int16_t val) const
{
	return data == (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator==(uint16_t val) const
{
	return data == (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator==(int val) const
{
	return data == (int64_t)val * __FLOAT_PT_INT;
}
bool _float::operator!=(const _float &f) const
{
	return !(this->operator==(f));
}
bool _float::operator!=(float val) const
{
	return !(this->operator==(val));
}
bool _float::operator!=(double val) const
{
	return !(this->operator==(val));
}
bool _float::operator!=(int16_t val) const
{
	return !(this->operator==(val));
}
bool _float::operator!=(uint16_t val) const
{
	return !(this->operator==(val));
}
bool _float::operator!=(int val) const
{
	return !(this->operator==(val));
}
#endif
_float &_float::operator=(const _float &f)
{
	data = f.data;
	return *this;
}
_float &_float::operator=(float f)
{
	data = f * __FLOAT_PT_FLOAT;
	return *this;
}
_float &_float::operator=(double d)
{
	data = d * __FLOAT_PT_DOUBLE;
	return *this;
}
_float &_float::operator=(int i)
{
	data = i;
	data *= __FLOAT_PT_INT;
	return *this;
}
_float &_float::operator=(unsigned int i)
{
	if (i > 0x7FFFFFFF)
	{
		i = 0x7FFFFFFF;
	}
	data = (int32_t)i;
	data *= __FLOAT_PT_INT;
	return *this;
}
_float &_float::operator=(uint32_t i)
{
	if (i > 0x7FFFFFFF)
	{
		i = 0x7FFFFFFF;
	}
	data = (int32_t)i;
	data *= __FLOAT_PT_INT;
	return *this;
}
_float::operator int() const
{
	return data / __FLOAT_PT_INT;
}

_float::operator unsigned int() const
{
	return data / __FLOAT_PT_INT;
}

_float::operator float() const
{
	return (float)data / __FLOAT_PT_FLOAT;
}

_float::operator double() const
{
	return (double)data / __FLOAT_PT_DOUBLE;
}

_float::operator uint32_t() const
{
	return data / __FLOAT_PT_INT;
}

_float::operator uint8_t() const
{
	return data / __FLOAT_PT_INT;
}

void _float::print(char *str) const
{
	print(str, 1);
}

void _float::print(char *str, uint8_t digits_bef_comma) const
{
	if (str)
	{
		int32_t iNum = 0;
		if (data >= 0)
			iNum = data;
		if (digits_bef_comma >= 2)
		{
			str[4] = (iNum % 10) + 48;
		}
		iNum /= 10;
		if (digits_bef_comma >= 1)
		{
			str[3] = (iNum % 10) + 48;
			str[2] = '.';
		}
		iNum /= 10;
		str[1] = (iNum % 10) + 48;
		iNum /= 10;
		str[0] = (iNum % 10) + 48;
	}
}

uint64_t _float::getData() const
{
	return data;
}

_float _float::direct(int64_t val)
{
	_float f;
	f.data = val;
	return f;
}

size_t _float::serialize(uint8_t *buffer, size_t len, const _float *val)
{
	if (buffer == nullptr || len < 8 || val == nullptr || val->data < 0)
	{
		return 0;
	}
	__TRACE("ser:");
	uint8_t *it = buffer;
	*(it++) = val->data;
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 8);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 16);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 24);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 32);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 40);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 48);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	*(it++) = (val->data >> 56);
	__TRACE((unsigned long)*it);
	__TRACE(' ');
	__TRACE((long)val->data);
	__TRACE(' ');
	__TRACELN((long)*buffer);
	return it - buffer;
}

size_t _float::deserialize(const uint8_t *buffer, size_t len, _float *val)
{
	if (buffer == nullptr || len < 8 || val == nullptr)
	{
		return 0;
	}
	__TRACE("des:");
	const uint8_t *it = buffer;
	uint64_t tmp = 0;
	val->data = 0;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp << 8;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp << 16;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp << 24;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp << 32;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp << 40;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	__TRACE(' ');
	val->data += tmp << 48;
	tmp = *(it++);
	__TRACE((unsigned long)tmp);
	val->data += tmp << 56;
	__TRACE(' ');
	__TRACE((long)val->data);
	__TRACE(' ');
	__TRACELN((long)*buffer);
	return it - buffer;
}

#endif
