#ifndef _CONTROLLED_OUTPUT_CPP_
#define _CONTROLLED_OUTPUT_CPP_

#include "ControlledOutput.h"

CControlledOutput::CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch, int32_t pin_set_sw_val, ControlledPinMode sm, ControlledPinMode im)
  :
  mSetModeSwitch(pin_set_mode_switch),
  mIsModeSwitch(pin_is_mode_switch),
  mSetSwitchVal(pin_set_sw_val)
{
  this->mPinSetOut = pin_set_out;
  this->mPinSetIn = pin_set_in;
  this->mPinSetUPre = pin_set_u_pre;
  this->mPinSetU = pin_set_u;
  this->mPinIsU = pin_is_u;
  this->mPinIsRes = pin_is_res;
  this->mSetMode = sm;
  this->mIsMode = im;
}
CControlledOutput::CControlledOutput(int32_t pin_set_out, int32_t pin_set_in, int32_t pin_set_u_pre, int32_t pin_set_u, int32_t pin_set_mode_switch, int32_t pin_is_u, int32_t pin_is_res, int32_t pin_is_mode_switch)
  :
  CControlledOutput(pin_set_out, pin_set_in, pin_set_u_pre, pin_set_u, pin_set_mode_switch, pin_is_u, pin_is_res, pin_is_mode_switch, -1, Voltage, Current)
{
}


void CControlledOutput::begin()
{
  pinMode(mPinIsRes, OUTPUT);
  mSetModeSwitch.begin();
  mIsModeSwitch.begin();
  mSetSwitchVal.begin();
  setIsMode(this->mIsMode);
}

ControlledPinMode CControlledOutput::getSetMode() const
{
  return this->mSetMode;
}

ControlledPinMode CControlledOutput::getIsMode() const
{
  return this->mIsMode;
}

_float CControlledOutput::getSetValIn() const
{
  _float f(stab_ana_read(mPinSetIn));
  f *= 12;
  f /= 4096;
  return f;
}

_float CControlledOutput::getSetVal() const
{
  if (mSetMode == Voltage)
  {
    return getSetU();
  }
  else {
    return getSetI();
  }
}

_float CControlledOutput::getSetU() const
{
  _float f(stab_ana_read(mPinSetU));
  f *= 12;
  f /= 4096;
  return f;
}

_float CControlledOutput::getSetI() const
{
  _float upre(stab_ana_read(mPinSetUPre));
  _float u(stab_ana_read(mPinSetU));

  upre *= 12;   //Anpassung 3V referenz
  upre /= 4096;

  u *= 12;      // Anpassung 3V referenz
  u /= 4096;

  _float ishunt = upre;
  ishunt -= u;
  ishunt *= 1000;		// Skalierung mA
  ishunt /= 220;		// Shunt Wiederstand 220 Ohm

  _float imessb = u;
  imessb /= 40;		// skalierung mA + 40k Ohm Messb.

  _float iventil = ishunt;
  iventil -= imessb;

  return iventil;//_float::direct((long)(100.0*iventil));
}

_float CControlledOutput::getIsVal() const
{
  return (mIsMode == Voltage ? getIsU() : getIsI());
}

_float CControlledOutput::getIsU() const
{
  _float f(stab_ana_read(mPinIsU));
  f *= 12;
  f /= 4096;
  return f;
}

_float CControlledOutput::getIsI() const
{
  _float f(stab_ana_read(mPinIsU));

  f *= 12;  // Anpassung 3V
  f /= 4096;

  // /=444.4444 da Wiederstand im Strommessbetrieb = 444.444 Ohm
  // *=1000 anpassung nach mA

  f *= 100000;
  f /= 44444;

  return f;
}

void CControlledOutput::update()
{
  //Setze den Sollwert für Ausgang
  if (!mSetSwitchVal.aktive() || mSetSwitchVal.wasPressed()) {
    _float f = getSetValIn();
    if (mSetMode == Voltage) {
      f *= 325;
    } else {
      f *= 210;
      f += 500;
    }
    analogWrite(mPinSetOut, f.getData() / 100);
  }
  if (mSetModeSwitch.wasPressed())setSetMode(mSetMode == Voltage ? Current : Voltage);

  //set Measurement Resistance in case of Mode change
  if (mIsModeSwitch.wasPressed())setIsMode(mIsMode == Voltage ? Current : Voltage);
}

uint8_t CControlledOutput::show(char* set_val, char* set_mode, char* is_val, char* is_mode)
{
  if (mDispMode == Normal) {
    // Print Set Value
    getSetVal().print(set_val);
    if (set_val) {
      if (mSetMode == Voltage) {
        set_mode[0] = 'V';
        set_mode[1] = ' ';
      }
      else {
        set_mode[0] = 'm';
        set_mode[1] = 'A';
      }
    }

    // Print Is Actual Value in RKP
    getIsVal().print(is_val);
    if (is_mode) {
      if (getIsMode() == Voltage) {
        is_mode[0] = 'V';
        is_mode[1] = ' ';
      }
      else {
        is_mode[0] = 'm';
        is_mode[1] = 'A';
      }
    }
  }
  else if (mDispMode == OldNewVal) {
    // Print Set Value
    getSetVal().print(set_val);
    if (set_mode) {
      if (mSetMode == Voltage) {
        set_mode[0] = 'V';
      }
    }

    // Print SetIn Val
    getSetValIn().print(is_val);
    if (set_mode) {
      if (mSetMode == Voltage) {
        is_mode[0] = 'V';
      }
    }
  }
  else if (mDispMode == Raw) {
    //printIntInt(&(str[2]), 4, analogRead(mPinSetUPre));
    //printIntInt(&(str[7]), 4, analogRead(mPinSetU));
    //printIntInt(&(str[12]), 4, analogRead(mPinIsU));
  }
  else if (mDispMode == Direct) {
    //printIntFloat(&(str[2]), 5, (analogRead(mPinSetIn) * 300) / 4096);
    //printIntFloat(&(str[8]), 5, (analogRead(mPinSetU) * 300) / 4096);
    //printIntFloat(&(str[14]), 5, (analogRead(mPinIsU) * 300) / 4096);
  }
  return 0xF;
}

uint8_t CControlledOutput::show(char* str) {
  return show(str + 10, str + 17, str + 30, str + 37);
}

void CControlledOutput::setSetMode(ControlledPinMode mode)
{
  this->mSetMode = mode;
}
void CControlledOutput::setIsMode(ControlledPinMode mode)
{
  this->mIsMode = mode;
  digitalWrite(mPinIsRes, (mode == Current ? LOW : HIGH));
}
void CControlledOutput::printFloat(char* str, int32_t length, int32_t iNum)
{
  if (iNum < 0) iNum = 0;
  if (5 > length) return;
  str[4] = (iNum % 10) + 48;
  iNum /= 10;
  str[3] = (iNum % 10) + 48;
  iNum /= 10;
  str[2] = '.';
  str[1] = (iNum % 10) + 48;
  iNum /= 10;
  str[0] = (iNum % 10) + 48;
}

void CControlledOutput::printInt(char* str, int32_t length, int32_t iNum) {
  if (iNum < 0) iNum = 0;
  if (4 > length) return;
  str[3] = (iNum % 10) + 48;
  iNum /= 10;
  str[2] = (iNum % 10) + 48;
  iNum /= 10;
  str[1] = (iNum % 10) + 48;
  iNum /= 10;
  str[0] = (iNum % 10) + 48;
}
uint32_t CControlledOutput::stab_ana_read(int32_t pin) {
  uint64_t sum = 0;
  const long valCount = 1 << 9;
  for (long cnt = 0; cnt < valCount; cnt++) {
    sum += analogRead(pin);
  }
  return sum / valCount;
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
