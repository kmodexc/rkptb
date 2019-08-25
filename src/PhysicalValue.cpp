#include "PhysicalValue.h"

using namespace rkp;

PhysicalValue::PhysicalValue()
	: value(0),
	  unit(Unit::Volt)
{
}

PhysicalValue::PhysicalValue(const _float &val, Unit un)
	: value(val),
	  unit(un)
{
}

Unit PhysicalValue::getUnit() const
{
	return unit;
}

PhysicalValue PhysicalValue::directVolt(uint32_t val)
{
	return PhysicalValue(_float::direct(val), Unit::Volt);
}
PhysicalValue PhysicalValue::directAmps(uint32_t val)
{
	return PhysicalValue(_float::direct(val), Unit::MilliAmps);
}
size_t PhysicalValue::serialize(uint8_t *buffer, size_t len) const
{
	if (buffer == nullptr || len < 8)
		return 0;
	uint8_t *it = buffer;
	*(it++) = static_cast<uint8_t>(unit);
	it += value.serialize(it,len - 1);
	return it - buffer;
}
size_t PhysicalValue::deserialize(const uint8_t *buffer, size_t len, PhysicalValue *val)
{
	if (buffer == nullptr || len < 9 || val == nullptr)
		return 0;
	const uint8_t *it = buffer;
	uint8_t tmp;
	tmp = *(it++);
	val->unit = static_cast<Unit>(tmp);
	it += _float::deserialize(it,len-1,&(val->value));
	return it - buffer;
}