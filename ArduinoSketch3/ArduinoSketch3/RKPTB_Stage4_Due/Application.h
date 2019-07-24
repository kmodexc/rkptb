#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <Arduino.h>
#include <Wire.h>
#include "ControlledOutput.h"
#include "Measurement.h"
#include "Display.h"

#include "pindefs.h"

class Application{
	Measurement ms1;

	//CControlledOutput Constructor sets pins for the Output
	//(pin_set_out, pin_set_in,  pin_set_u_pre,  pin_set_u,  pin_set_mode_switch,  pin_is_u, pin_is_res, pin_is_mode_switch)
	//                      so, si,sup,su,sms,iu, ir,ims
	CControlledOutput q_set;
	CControlledOutput p_set;
	CControlledOutput parSet;

	CKey keyDispMode;

	Display disp;

	DisplayText stat;

	DisplayText p_setVal;
	DisplayText p_setMode;
	DisplayText p_isVal;
	DisplayText p_isMode;
	
	DisplayText q_setVal;
	DisplayText q_setMode;
	DisplayText q_isVal;
	DisplayText q_isMode;
	
	DisplayText ps_setVal;
	DisplayText ps_isVal;

	public:
	Application();
	void initialize();
	void loop(unsigned long cnt);
};

#endif
