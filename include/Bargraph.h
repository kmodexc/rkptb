#pragma once

#include "Graphics.h"
#include "_float.h"

namespace RKP
{
class Bargraph
{
	size_t x;
	size_t y;
	uint8_t code;
	_float min;
	_float max;
	_float val;
	const char *label;
	bool update_val;
	bool update_skale;

public:
	Bargraph(size_t x, size_t y, uint8_t code, const char *label);

	void repaint(Graphics *);
	bool loop(uint64_t loopCount, Graphics *disp);
	void unshow(Graphics *);

	void setValue(const _float &val);
	_float getValue() const;

	void setRange(const _float &min,const _float &max);

private:
	uint8_t valToBg(_float) const;
	_float bgToVal(uint8_t) const;
};
} // namespace Display