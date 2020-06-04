#pragma once

namespace rkp
{

	class StatePin
	{
	private:
		bool output;
		int pin;
		int state;
		int modulo;
		bool newValue;
	public:
		StatePin(int pin, int startState, int modulo, bool output);
		void init();
		int getState();
		void setState(int state,bool hasNewVal);
		void update();
		bool hasNewValue();
	};

} // namespace rkp