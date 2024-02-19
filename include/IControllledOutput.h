#pragma once

#include "PhysicalValue.h"
#include "ControlledPinMode.h"

class IControlledOutput
{
public:
	virtual ControlledPinMode getSetMode() const = 0;
	virtual ControlledPinMode getIsMode() const = 0;
	virtual rkp::PhysicalValue getSetValIn() = 0;
	virtual rkp::PhysicalValue getSetVal() = 0;
	virtual rkp::PhysicalValue getSetU() = 0;
	virtual rkp::PhysicalValue getSetI() = 0;
	virtual rkp::PhysicalValue getIsVal() = 0;
	virtual rkp::PhysicalValue getIsU() = 0;
	virtual rkp::PhysicalValue getIsI() = 0;

	virtual uint32_t getUAdcRaw() = 0;
	virtual uint32_t getUPreAdcRaw() = 0;

	virtual void setSetVal(rkp::PhysicalValue val) = 0;
	
	virtual void setSetMode(ControlledPinMode mode) = 0;
	virtual void setIsMode(ControlledPinMode mode) = 0;
};
