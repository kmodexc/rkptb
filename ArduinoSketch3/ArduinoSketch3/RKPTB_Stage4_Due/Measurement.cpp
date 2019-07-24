#ifdef _MEASUREMENT_CPP_
#define _MEASUREMENT_CPP_

#include <Arduino.h>

_float Measurement::set_u_direct(int32_t pin){
	return _float::direct(analogRead(pin));
}

_float Measurement::set_i_direct(int32_t pup,int32_t pu){
	_float upre = _float::direct(analogRead(pup));
	_float u = _float::direct(analogRead(pu));

	_float ishunt = upre;
	ishunt -= u;
	ishunt *= 1000;		// Skalierung mA
	ishunt /= 220;		// Shunt Wiederstand 220 Ohm

	_float imessb = u;
	imessb /= 40;		// skalierung mA + 40k Ohm Messb.

	_float iventil = ishunt;
	iventil -= imessb;

	return iventil;
}

_float Measurement::is_u_direct(int32_t pin){
	return _float::direct(analogRead(pin));
}

_float Measurement::is_i_direct(int32_t pin){
	_float f = _float::direct(analogRead(pin));
	// implizit anpassung 1024 -> 10.24 durch directe anpassung
	// /=444.4444 da Wiederstand im Strommessbetrieb = 444.444 Ohm
	// *=1000 anpassung nach mA

	f *= 100000; 
	f /= 44444;
	return f;
}

#endif
