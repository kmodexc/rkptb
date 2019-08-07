#pragma once

#include "Page.h"

class MenuPage : public Page{
    public:
    // Initialization
	virtual void initialize(Graphics*) override;

    // repaint the whole page (clear and pait evrything)
    virtual void repaint(Graphics*) override;
	
	// Update loop
	virtual void loop(uint64_t loopCount,Graphics* disp) override;
};