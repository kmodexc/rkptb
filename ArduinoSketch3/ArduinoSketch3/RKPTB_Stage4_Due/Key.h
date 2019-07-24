#ifndef _KEY_H_
#define _KEY_H_

#include "Arduino.h"

class CKey
{
	int32_t mPin;
	bool mLastState;
public:
	CKey(int32_t pin);
	void begin();
	bool wasPressed();
  bool aktive();
protected:
	bool isPressed();
};

#endif
