#ifndef _CONTROLLED_OUTPUT_H_
#define _CONTROLLED_OUTPUT_H_

#include "Arduino.h"
#include "Key.h"
#include "PhysicalValue.h"
#include <Wire.h>
#include "Measurement.h"
#include "MeasurePin.h"
#include "ControlledPinMode.h"


class CControlledOutput
{
	int32_t mPinSetOut;
	MeasurePin mPinSetIn;
	MeasurePin mPinSetUPre;
	MeasurePin mPinSetU;
	MeasurePin mPinIsU;
	int32_t mPinIsRes;
	CKey mSetModeSwitch;
	CKey mIsModeSwitch;
	CKey mSetSwitchVal;
	ControlledPinMode mSetMode;
	ControlledPinMode mIsMode;

public:
	CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch);
	CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch, int32_t pin_set_sw_val, ControlledPinMode sm, ControlledPinMode im);
	void begin();

	void measure();

	ControlledPinMode getSetMode() const;
	ControlledPinMode getIsMode() const;
	rkp::PhysicalValue getSetValIn();
	rkp::PhysicalValue getSetVal();
	rkp::PhysicalValue getSetU();
	rkp::PhysicalValue getSetI();
	rkp::PhysicalValue getIsVal();
	rkp::PhysicalValue getIsU();
	rkp::PhysicalValue getIsI();

	uint32_t getUAdcRaw();
	uint32_t getUPreAdcRaw();

	void setSetVal(rkp::PhysicalValue val);
	
	void setSetMode(ControlledPinMode mode);
	void setIsMode(ControlledPinMode mode);

	void update();
};

#endif
