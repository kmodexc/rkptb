#pragma once

#include "Page.h"

class NumberPage : public Page
{
	float mVal;

public:
	// Initialization
	virtual void initialize(Graphics *) override;

	// repaint the whole page (clear and pait evrything)
	virtual void repaint(Graphics *) override;

	// request function for touch events
	virtual TouchEvent getTouchEvent() override;
	virtual uint8_t *getTouchData() override;

	// Update loop
	virtual void loop(uint64_t loopCount, Graphics *disp) override;

	virtual void unshow(Graphics *) override;

	float getValue();
};