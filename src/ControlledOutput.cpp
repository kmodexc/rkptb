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
	setSetVal(_float::direct(0));
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

_float CControlledOutput::getSetValIn()
{
	_float f(mPinSetIn.getVal());
	f *= 12;
	f /= 4096;
	return f;
}

_float CControlledOutput::getSetVal()
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

_float CControlledOutput::getSetU()
{
	return set_u_double_rounded(mPinSetU.getVal());
}

_float CControlledOutput::getSetI()
{
	return set_i_double_rounded(mPinSetUPre.getVal(), mPinSetU.getVal());
}

_float CControlledOutput::getIsVal()
{
	return (mIsMode == ControlledPinMode::Voltage ? getIsU() : getIsI());
}

_float CControlledOutput::getIsU()
{
	return is_u_double_rounded(mPinIsU.getVal());
}

_float CControlledOutput::getIsI()
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

void CControlledOutput::setSetVal(_float val)
{
	val = constrain(val,_float(0),_float(11));
	if (mSetMode == ControlledPinMode::Voltage)
	{
		val *= 325;
	}
	else
	{
		val *= 210;
		val += 500;
	}
	analogWrite(mPinSetOut, val);
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

uint8_t CControlledOutput::show(char *set_val, char *set_mode, char *is_val, char *is_mode)
{
	if (mDispMode == Normal)
	{
		// Print Set Value
		getSetVal().print(set_val);
		if (set_val)
		{
			if (mSetMode == ControlledPinMode::Voltage)
			{
				set_mode[0] = 'V';
				set_mode[1] = ' ';
			}
			else
			{
				set_mode[0] = 'm';
				set_mode[1] = 'A';
			}
		}

		// Print Is Actual Value in RKP
		getIsVal().print(is_val);
		if (is_mode)
		{
			if (getIsMode() == ControlledPinMode::Voltage)
			{
				is_mode[0] = 'V';
				is_mode[1] = ' ';
			}
			else
			{
				is_mode[0] = 'm';
				is_mode[1] = 'A';
			}
		}
	}
	else if (mDispMode == OldNewVal)
	{
		// Print Set Value
		getSetVal().print(set_val);
		if (set_mode)
		{
			if (mSetMode == ControlledPinMode::Voltage)
			{
				set_mode[0] = 'V';
			}
		}

		// Print SetIn Val
		getSetValIn().print(is_val);
		if (set_mode)
		{
			if (mSetMode == ControlledPinMode::Voltage)
			{
				is_mode[0] = 'V';
			}
		}
	}
	else if (mDispMode == Raw)
	{
		//printIntInt(&(str[2]), 4, analogRead(mPinSetUPre));
		//printIntInt(&(str[7]), 4, analogRead(mPinSetU));
		//printIntInt(&(str[12]), 4, analogRead(mPinIsU));
	}
	else if (mDispMode == Direct)
	{
		//printIntFloat(&(str[2]), 5, (analogRead(mPinSetIn) * 300) / 4096);
		//printIntFloat(&(str[8]), 5, (analogRead(mPinSetU) * 300) / 4096);
		//printIntFloat(&(str[14]), 5, (analogRead(mPinIsU) * 300) / 4096);
	}
	return 0xF;
}

uint8_t CControlledOutput::show(char *str)
{
	return show(str + 10, str + 17, str + 30, str + 37);
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

void CControlledOutput::setDisplayMode(DisplayMode m)
{
	this->mDispMode = m;
}
DisplayMode CControlledOutput::getDisplayMode()
{
	return this->mDispMode;
}

#endif
