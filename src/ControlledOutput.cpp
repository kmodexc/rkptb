#ifndef _CONTROLLED_OUTPUT_CPP_
#define _CONTROLLED_OUTPUT_CPP_

#include "ControlledOutput.h"

using namespace rkp;
using namespace rkp::r10k;

CControlledOutput::CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch, int32_t pin_set_sw_val, ControlledPinMode sm, ControlledPinMode im)
	: mPinSetIn(pin_set_in),
	  mPinSetUPre(pin_set_u_pre),
	  mPinSetU(pin_set_u),
	  mPinIsU(pin_is_u),
	  mSetModeSwitch(pin_set_mode_switch),
	  mIsModeSwitch(pin_is_mode_switch),
	  mSetSwitchVal(pin_set_sw_val)
{
	this->mPinSetOut = pin_set_out;
	this->mPinIsRes = pin_is_res;
	this->mSetMode = sm;
	this->mIsMode = im;
}
CControlledOutput::CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch)
	: CControlledOutput(pin_set_out, pin_set_in, pin_set_u_pre, pin_set_u, pin_set_mode_switch, pin_is_u, pin_is_res, pin_is_mode_switch, -1, ControlledPinMode::Voltage, ControlledPinMode::Current)
{
}

void CControlledOutput::begin()
{
	pinMode(mPinIsRes, OUTPUT);
	mSetModeSwitch.begin();
	mIsModeSwitch.begin();
	mSetSwitchVal.begin();
	setIsMode(this->mIsMode);
	setSetVal(PhysicalValue());
}

void CControlledOutput::measure()
{
	mPinSetIn.reset();
	mPinSetUPre.reset();
	mPinSetU.reset();
	mPinIsU.reset();
}

ControlledPinMode CControlledOutput::getSetMode() const
{
	return this->mSetMode;
}

ControlledPinMode CControlledOutput::getIsMode() const
{
	return this->mIsMode;
}

PhysicalValue CControlledOutput::getSetValIn()
{
	PhysicalValue f(mPinSetIn.getVal(),rkp::Unit::Volt);
	f.value *= 12;
	f.value /= 4096;
	return f;
}

PhysicalValue CControlledOutput::getSetVal()
{
	if (mSetMode == ControlledPinMode::Voltage)
	{
		return getSetU();
	}
	else
	{
		return getSetI();
	}
}

PhysicalValue CControlledOutput::getSetU()
{
	return set_u_double_rounded(mPinSetU.getVal());
}

PhysicalValue CControlledOutput::getSetI()
{
	return set_i_double_rounded(mPinSetUPre.getVal(), mPinSetU.getVal());
}

PhysicalValue CControlledOutput::getIsVal()
{
	return (mIsMode == ControlledPinMode::Voltage ? getIsU() : getIsI());
}

PhysicalValue CControlledOutput::getIsU()
{
	return is_u_double_rounded(mPinIsU.getVal());
}

PhysicalValue CControlledOutput::getIsI()
{
	return is_i_double_rounded(mPinIsU.getVal());
}

uint32_t CControlledOutput::getUAdcRaw()
{
	return mPinSetU.getVal();
}

uint32_t CControlledOutput::getUPreAdcRaw()
{
	return mPinSetUPre.getVal();
}

void CControlledOutput::setSetVal(PhysicalValue val)
{
	if (val.getUnit() == rkp::Unit::Volt)
	{
		val.value *= 325;
	}
	else
	{
		val.value *= 210;
		val.value += 500;
	}
	analogWrite(mPinSetOut, constrain((int)val.value,0,4095));
}

void CControlledOutput::update()
{
	//Setze den Sollwert für Ausgang
	if (!mSetSwitchVal.aktive() || mSetSwitchVal.wasPressed())
	{
		setSetVal(getSetValIn());
	}
	// update mode switch
	if (mSetModeSwitch.wasPressed())
		setSetMode(mSetMode == ControlledPinMode::Voltage ? ControlledPinMode::Current : ControlledPinMode::Voltage);
	if (mIsModeSwitch.wasPressed())
		setIsMode(mIsMode == ControlledPinMode::Voltage ? ControlledPinMode::Current : ControlledPinMode::Voltage);
}

void CControlledOutput::setSetMode(ControlledPinMode mode)
{
	this->mSetMode = mode;
}
void CControlledOutput::setIsMode(ControlledPinMode mode)
{
	this->mIsMode = mode;
	digitalWrite(mPinIsRes, (mode == ControlledPinMode::Current ? LOW : HIGH));
}

#endif
