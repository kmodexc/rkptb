#include "StatePin.h"
#include "Arduino.h"

namespace rkp
{

	StatePin::StatePin(int pin, int startState, int modulo, bool output)
	{
		this->pin = pin;
		this->state = startState;
		this->modulo = modulo;
		this->output = output;
	}
	void StatePin::init()
	{
		if (output)
		{
			pinMode(pin, OUTPUT);
		}
	}
	int StatePin::getState()
	{
		return state;
	}
	void StatePin::setState(int state)
	{
		if (output)
		{
			if (state && !this->state)
			{
				digitalWrite(pin, HIGH);
			}
			else if (!state && this->state)
			{
				digitalWrite(pin, LOW);
			}
		}
		this->state = state;
	}
	void StatePin::update()
	{
		if (!output)
		{
			int newState = digitalRead(pin);
			if (newState != state)
			{
				newValue = true;
			}
			state = newState;
		}
	}
	bool StatePin::hasNewValue()
	{
		if (newValue)
		{
			newValue = false;
			return true;
		}
		return false;
	}

} // namespace rkp