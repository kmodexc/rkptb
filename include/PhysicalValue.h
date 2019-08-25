#pragma once

#include "_float.h"

namespace rkp
{

enum class Unit
{
	Volt,
	MilliAmps
};

class PhysicalValue
{
	Unit unit;

public:
	_float value;

public:
	PhysicalValue();
	PhysicalValue(const _float &, Unit);
	Unit getUnit() const;
	static PhysicalValue directVolt(uint32_t val);
	static PhysicalValue directAmps(uint32_t val);

	size_t serialize(uint8_t *buffer, size_t len) const;
	static size_t deserialize(const uint8_t *buffer, size_t len, PhysicalValue *val);
};

} // namespace rkp