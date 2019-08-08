#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <Arduino.h>
#include <Wire.h>
#include "ControlledOutput.h"
#include "Measurement.h"
#include "DisplayManager.h"

#include "pindefs.h"

class Application{

	//CControlledOutput Constructor sets pins for the Output
	//(pin_set_out, pin_set_in,  pin_set_u_pre,  pin_set_u,  pin_set_mode_switch,  pin_is_u, pin_is_res, pin_is_mode_switch)
	//                      so, si,sup,su,sms,iu, ir,ims
	CControlledOutput q_set;
	CControlledOutput p_set;
	CControlledOutput parSet;

	DisplayManager disp_man;

	public:
	Application();
	void initialize();
	void loop(unsigned long cnt);
};

#endif
