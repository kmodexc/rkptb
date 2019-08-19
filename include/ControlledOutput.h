#ifndef _CONTROLLED_OUTPUT_H_
#define _CONTROLLED_OUTPUT_H_

#include "Arduino.h"
#include "Key.h"
#include "_float.h"
#include <Wire.h>
#include "Measurement.h"
#include "MeasurePin.h"
#include "ControlledPinMode.h"

enum DisplayMode
{
	Normal,
	OldNewVal,
	Raw,
	Direct
};

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
	DisplayMode mDispMode;

public:
	CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch);
	CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch, int32_t pin_set_sw_val, ControlledPinMode sm, ControlledPinMode im);
	void begin();

	void measure();

	ControlledPinMode getSetMode() const;
	ControlledPinMode getIsMode() const;
	_float getSetValIn();
	_float getSetVal();
	_float getSetU();
	_float getSetI();
	_float getIsVal();
	_float getIsU();
	_float getIsI();

	uint32_t getUAdcRaw();
	uint32_t getUPreAdcRaw();

	void setSetVal(_float val);
	
	void setSetMode(ControlledPinMode mode);
	void setIsMode(ControlledPinMode mode);

	void update();

	uint8_t show(char *set_val, char *set_mode, char *is_val, char *is_mode);
	uint8_t show(char *str);
	void setDisplayMode(DisplayMode mode);
	DisplayMode getDisplayMode();
};

#endif
