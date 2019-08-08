#include "Measurement.h"

_float rkp::u_adc_direct(uint32_t adc)
{
	return _float::direct((adc * 75) / 1024);
}

_float rkp::set_u_direct(uint32_t u)
{
	_float f(u);
	f *= 12;
	f /= 4096;
	return f;
}

_float rkp::set_u_double_rounded(uint32_t u)
{
	double dbl_u = u;
	dbl_u *= 0.29296875;
	return _float::direct((long)dbl_u);
}

_float rkp::r10k::set_i_direct(uint32_t adc_up, uint32_t adc_u)
{
	return _float::direct((15L*(2000L*((long)adc_up)-2011L*((long)adc_u)))/22528L);
}

_float rkp::r10k::set_i_double_exact(uint32_t upre_adc, uint32_t u_adc)
{
	double dbl_upre = 0.0;
	double dbl_u = 0.0;

	dbl_upre = (double)(upre_adc * 3);
	dbl_upre /= 4096.0;
	dbl_u = (double)(u_adc * 3);
	dbl_u /= 4096.0;

	// u shunt
	double du = dbl_upre;
	du -= dbl_u;
	// i shunt
	double is = du;
	is *= 4.0;	// volt div
	is *= 1000.0; // to mA
	is /= 220.0;  // r shunt
	// i second voltage divider
	double im = dbl_u;
	im /= 10.0; // 4000 Ohm but to mA (*1000) and volt-div (*4)
	// i ventil
	double iv = is;
	iv -= im;

	return _float::direct((long)(iv * 100.0));
}

_float rkp::r10k::set_i_double_rounded(uint32_t up, uint32_t u)
{
	return _float::direct((long)((-1.339) * (u - 0.99453 * up)));
}

_float rkp::is_u_direct(uint32_t is)
{
	_float f(is);
	f *= 12;
	f /= 4096;
	return f;
}

_float rkp::is_u_double_rounded(uint32_t is)
{
	double dbl_u = is;
	dbl_u *= 0.29296875;
	return _float::direct((long)dbl_u);
}

_float rkp::is_i_direct(uint32_t is)
{
	_float f(is);
	// implizit anpassung 1024 -> 10.24 durch directe anpassung
	// /=444.4444 da Wiederstand im Strommessbetrieb = 444.444 Ohm
	// *=1000 anpassung nach mA

	f *= 12;
	f *= 100000;
	f /= 4096;
	f /= 44444;
	return f;
}

_float rkp::is_i_double_rounded(uint32_t is)
{
	double dbl_is = is;
	dbl_is *= 0.6591797;
	return _float::direct((long)dbl_is);
}

uint32_t rkp::stab_ana_read(uint8_t pin)
{
	return stab_ana_read(pin, (1 << 8));
}

uint32_t rkp::stab_ana_read(uint8_t pin, uint32_t valCount)
{
	uint64_t sum = 0;
	for (uint32_t cnt = 0; cnt < valCount; cnt++)
	{
		sum += analogRead(pin);
	}
	return sum / valCount;
}