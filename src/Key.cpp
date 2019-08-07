#ifndef _KEY_CPP_
#define _KEY_CPP_

#include "Key.h"

CKey::CKey(int32_t pin)
{
  this->mPin = pin;
}
void CKey::begin()
{
  // The Button conntects if pressed to GND
  // otherwise its int32_ternally pulled up
  if(mPin < 0) return;
  pinMode(mPin,INPUT_PULLUP);
}
bool CKey::wasPressed()
{
  bool state = isPressed();
  if (state != mLastState)
  {
    mLastState = state;
    return !state;
  }
  return false;
}
bool CKey::aktive(){
  return mPin >= 0;
}
bool CKey::isPressed()
{
  // The Button conntects if pressed to GND
  // otherwise its int32_ternally pulled up
  if(mPin < 0) return false;
  return !digitalRead(mPin);
}

#endif
