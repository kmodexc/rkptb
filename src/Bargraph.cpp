#include "Bargraph.h"

using namespace RKP;

Bargraph::Bargraph(size_t x, size_t y, uint8_t code, const char *label)
{
	this->x = x;
	this->y = y;
	this->code = code;
	this->min = 0;
	this->max = 11;
	this->val = 0;
	this->label = label;
}

void Bargraph::repaint(Graphics *pg)
{
	pg->createBargraph(x, y, code, label);
	pg->updateBargraphSkale(x,y,code,min,max);
	pg->setBargraphVal(code, valToBg(val));
}

bool Bargraph::loop(uint64_t loopCount, Graphics *pg)
{
	if(update_skale){
		pg->updateBargraphSkale(x,y,code,min,max);
		TRACE("update skale ");
		TRACE((int)min);
		TRACE(" ");
		TRACELN((int)max);
		update_skale = false;
		return true;
	}else if(update_val){
		pg->setBargraphVal(code, valToBg(val));
		update_val = false;
		return true;
	}
	return false;
}

void Bargraph::unshow(Graphics *)
{
	// to do ...
}

void Bargraph::setValue(const _float &val)
{
	this->val = val;
	update_val = true;
}

_float Bargraph::getValue() const
{
	return val;
}

void Bargraph::setRange(const _float &min,const _float &max){
	this->min = min;
	this->max = max;
	update_skale = true;
}

TouchEvent Bargraph::bargraphChangeEvent(TouchEvent te,uint8_t* data){
	if(data == nullptr) return te;
	this->val = bgToVal(*data);
	return TouchEvent::nothing;
}

uint8_t Bargraph::valToBg(_float f) const
{
	TRACE("valtoBG ");
	TRACE((int)f);
	f -= min;
	TRACE(" ");
	TRACE((int)f);
	f *= 254;
	TRACE(" ");
	TRACE((int)f);
	_float diff = max;
	diff -= min;
	TRACE(" ");
	TRACE((int)diff);
	f /= diff;
	TRACE(" ");
	TRACELN((int)f);
	return f;
}

_float Bargraph::bgToVal(uint8_t b) const
{
	_float diff = max;
	diff -= min;
	_float res = b;
	res *= diff;
	res /= 254;
	res += min;
	return res;
}