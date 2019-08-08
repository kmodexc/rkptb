#pragma once

#include <stdint.h>
#include "_float.h"
#include "Graphics.h"
#include "pindefs.h"

#define DISPM_REC_BUFFER_SIZE 10

enum Unit{
	Volt,
	MilliAmps
};

enum TouchEvent{
	nothing,
	q_set_mode_change,
	q_is_mode_change,
	p_set_mode_change,
	p_is_mode_change,
	ps_switch_val,
	go_menu_page,
	
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
};

namespace rkp{
	void unit_print(char*,Unit);
}


class Page{
    public:

    // Initialization
	virtual void initialize(Graphics*);

    // repaint the whole page (clear and pait evrything)
    virtual void repaint(Graphics*) = 0;
	
	// Setter for live values
	virtual void set_q_set(_float val,Unit un);
	virtual void set_q_is(_float val,Unit un);
	virtual void set_p_set(_float val,Unit un);
	virtual void set_p_is(_float val,Unit un);
	virtual void set_ps_pre_set(_float val,Unit un);
	virtual void set_ps_set(_float val,Unit un);
	
	// request function for touch events
	virtual TouchEvent getTouchEvent();
	virtual uint8_t getTouchValue();
	
	// Update loop
	virtual void loop(uint64_t loopCount,Graphics* disp);


	private:

	// receive buffer
	uint8_t rec_buffer[DISPM_REC_BUFFER_SIZE];
	
	// receive buffer touch events
	TouchEvent touchEvent;
	uint8_t eventVal;

	void readSendBuffer(Graphics*);

};