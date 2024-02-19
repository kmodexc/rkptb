#pragma once

#include <stdint.h>
#include "_float.h"
#include "Graphics.h"
#include "pindefs.h"
#include "PhysicalValue.h"
#include "TouchEvent.h"
#include "IControllledOutput.h"
#include "Context.h"

#define DISPM_REC_BUFFER_SIZE 10

// must be greater 8 bcs a double (8-bytes) is stored in it
#define TOUCH_EVENT_DATA_SIZE 20

enum class ControlMode
{
	TouchScreen,
	AnalogInputs
};

namespace rkp
{
void unit_print(char *, Unit);
}

class Page
{
public:
	// Initialization
	virtual void initialize(Graphics *);
	virtual void set_cont_output(IControlledOutput*, IControlledOutput*, IControlledOutput*);

	// repaint the whole page (clear and pait evrything)
	virtual void repaint(Graphics *);

	// Setter for live values
	virtual void update_context(const Context&);
	virtual void set_q_set(const rkp::PhysicalValue&);
	virtual void set_q_is(const rkp::PhysicalValue&);
	virtual void set_p_set(const rkp::PhysicalValue&);
	virtual void set_p_is(const rkp::PhysicalValue&);
	virtual void set_ps_pre_set(const rkp::PhysicalValue&);
	virtual void set_ps_set(const rkp::PhysicalValue&);
	virtual void set_error(const bool val, const bool newVal);
	virtual void set_release(const bool val, const bool newVal);

	// request function for touch events
	virtual TouchEvent getTouchEvent();
	virtual void *getTouchData();

	// Update loop
	virtual void loop(uint64_t loopCount, Graphics *disp);

	// methond to delete the screen
	virtual void unshow(Graphics *pg);

	virtual bool isVisible();

private:
	bool mVisible;

	// receive buffer
	uint8_t rec_buffer[DISPM_REC_BUFFER_SIZE];

	// receive buffer touch events
	TouchEvent touchEvent;
	uint8_t eventData[TOUCH_EVENT_DATA_SIZE];

	void readSendBuffer(Graphics *);
};