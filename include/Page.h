#pragma once

#include <stdint.h>
#include "_float.h"
#include "Graphics.h"
#include "pindefs.h"
#include "PhysicalValue.h"

#define DISPM_REC_BUFFER_SIZE 10

// must be greater 8 bcs a double (8-bytes) is stored in it
#define TOUCH_EVENT_DATA_SIZE 20

enum class TouchEvent
{
	nothing,
	q_set_mode_change,
	q_is_mode_change,
	p_set_mode_change,
	p_is_mode_change,
	ps_switch_val,
	go_menu_page,
	mem_q_tgl,
	mem_p_tgl,
	mem_ps_tgl,
	go_numpad_q,
	go_numpad_p,
	go_numpad_ps,

	ps_val_1,
	ps_val_2,
	ps_val_3,
	ps_val_4,
	ps_val_5,
	ps_val_6,
	ps_val_7,
	ps_val_8,
	ps_val_9,

	bar_graph_p,
	bar_graph_q,
	bar_graph_ps,

	menu_page_back,
	precision_toggle,
	go_current_page,
	go_about_page,
	go_analog_page,
	go_number_page,

	editbox_data_avail,
	number_page_enter,
	number_page_back,

	release_on,
	release_off,
	release_toggle
};

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

	// repaint the whole page (clear and pait evrything)
	virtual void repaint(Graphics *);

	// Setter for live values
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
	virtual uint8_t *getTouchData();

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