#ifndef _APPLICATION_CPP_
#define _APPLICATION_CPP_

#include "Application.h"

//CControlledOutput Constructor sets pins for the Output
//(pin_set_out, pin_set_in,  pin_set_u_pre,  pin_set_u,  pin_set_mode_switch,  pin_is_u, pin_is_res, pin_is_mode_switch)
//                      so, si,sup,su,sms,iu, ir,ims

Application::Application()
: q_set(7, 9, 1, 0, 37, 7, 47, 49),
p_set(6, 8, 6, 5, 35, 4, 45, 51),
parSet(5, 10, 3, 2, 24, 2, 26, 28, 53, Voltage, Voltage)
{
	//q_set.setDisplayMode(Raw);
	//p_set.setDisplayMode(Raw);
	parSet.setDisplayMode(OldNewVal);
}

void Application::initialize() {

	analogReadResolution(12);
	analogWriteResolution(12);

	q_set.begin();
	p_set.begin();
	parSet.begin();

	delay(1000);
	
	// Initialize display at last to wait until its ready
	disp_man.initialize();
}

void Application::loop(unsigned long loopCount) {
	// update Values of output
	q_set.update();
	p_set.update();
	parSet.update();

	//bool error = !digitalRead(PIN_ERROR);
	//bool mrel = !digitalRead(PIN_RELEASE);
	
	disp_man.set_q_set(q_set.getSetVal(),(Unit)q_set.getSetMode());
	
	disp_man.set_q_is(q_set.getIsVal(),(Unit)q_set.getIsMode());
	
	disp_man.set_p_set(p_set.getSetVal(),(Unit)p_set.getSetMode());
	
	disp_man.set_p_is(p_set.getIsVal(),(Unit)p_set.getIsMode());
	
	disp_man.set_ps_pre_set(parSet.getSetValIn(),(Unit)parSet.getSetMode());
	
	disp_man.set_ps_set(parSet.getSetVal(),(Unit)parSet.getSetMode());
	
	switch(disp_man.getTouchEvent()){
		case q_set_mode_change:
		q_set.setSetMode((q_set.getSetMode() == Voltage ? Current : Voltage));
		break;
		case p_set_mode_change:
		p_set.setSetMode((p_set.getSetMode() == Voltage ? Current : Voltage));
		break;
		case q_is_mode_change:
		q_set.setIsMode((q_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		case p_is_mode_change:
		p_set.setIsMode((p_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		
		case p_is_mode_change:
		break;
		
		case p_is_mode_change:
		p_set.setIsMode((p_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		
		case p_is_mode_change:
		p_set.setIsMode((p_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		
		case p_is_mode_change:
		p_set.setIsMode((p_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		
		case p_is_mode_change:
		p_set.setIsMode((p_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		
		case p_is_mode_change:
		p_set.setIsMode((p_set.getIsMode() == Voltage ? Current : Voltage));
		break;
		
		default:
		break;
	}
	
	disp_man.loop(loopCount);
}
#endif
