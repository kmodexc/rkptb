#ifndef _CONTROLLED_OUTPUT_H_
#define _CONTROLLED_OUTPUT_H_

#include "Arduino.h"
#include "Key.h"
#include "_float.h"
#include <Wire.h>
#include "Measurement.h"

enum ControlledPinMode {
  Voltage,
  Current
};

enum DisplayMode{
  Normal,OldNewVal,Raw,Direct
};

class CControlledOutput
{
  int32_t mPinSetOut;
  int32_t mPinSetIn;
  int32_t mPinSetUPre;
  int32_t mPinSetU;
  int32_t mPinIsU;
  int32_t mPinIsRes;
  CKey mSetModeSwitch;
  CKey mIsModeSwitch;
  CKey mSetSwitchVal;
  ControlledPinMode mSetMode;
  ControlledPinMode mIsMode;
  DisplayMode mDispMode;
public:
  CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch);
  CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch, int32_t pin_set_sw_val, ControlledPinMode sm,ControlledPinMode im);
  void begin();
  ControlledPinMode getSetMode() const;
  ControlledPinMode getIsMode() const;
  _float getSetValIn() const;
  _float getSetVal() const;
  _float getSetU() const;
  _float getSetI() const;
  _float getIsVal() const;
  _float getIsU() const;
  _float getIsI() const;
  void update();
  uint8_t show(char* set_val,char* set_mode,char* is_val,char* is_mode);
  uint8_t show(char* str);
  static void printFloat(char* str,int32_t length,int32_t num);
  static void printInt(char* str,int32_t length,int32_t num);
  void setDisplayMode(DisplayMode mode);
  DisplayMode getDisplayMode();
  static uint32_t stab_ana_read(int32_t pin);
  void setSetMode(ControlledPinMode mode);
  void setIsMode(ControlledPinMode mode);
};


#endif
