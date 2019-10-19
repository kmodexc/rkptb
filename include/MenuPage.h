#pragma once

#include "Page.h"

class MenuPage : public Page
{
public:
	// repaint the whole page (clear and pait evrything)
	virtual void repaint(Graphics *) override;
};