/*
* DisplayManager.h
*
* Created: 24.07.2019 15:58:38
* Author: Marius
*/


#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

#include "_float.h"
#include "Display.h"


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
	bar_graph_ps
};


class DisplayManager
{
	//variables
	public:
	protected:
	private:

	// Display
	Display disp;

	// Display texts for live values
	DisplayText dt_q;
	DisplayText dt_p;
	DisplayText dt_ps;
	
	// receive buffer
	uint8_t rec_buffer[DISPM_REC_BUFFER_SIZE];
	
	// receive buffer touch events
	TouchEvent te;
	uint8_t barval;

	//functions
	public:

	// Constructors
	DisplayManager();
	~DisplayManager();
	
	// Initialization
	void initialize();
	
	// Setter for live values
	void set_q_set(_float val,Unit un);
	void set_q_is(_float val,Unit un);
	void set_p_set(_float val,Unit un);
	void set_p_is(_float val,Unit un);
	void set_ps_pre_set(_float val,Unit un);
	void set_ps_set(_float val,Unit un);
	
	
	// request function for touch events
	TouchEvent getTouchEvent();
	uint8_t getBarValue();
	
	// function to read and interpret the send buffer
	void readSendBuffer();	
	
	// Update loop
	void loop(uint64_t loopCount);
	
	// Static helpers for Unit
	void unit_print(char* str,Unit u);
	
	
	protected:
	private:

}; //DisplayManager

#endif //__DISPLAYMANAGER_H__
