#ifndef _APPLICATION_CPP_
#define _APPLICATION_CPP_

#include "Application.h"

using namespace rkp;

//CControlledOutput Constructor sets pins for the Output
//(pin_set_out, pin_set_in,  pin_set_u_pre,  pin_set_u,  pin_set_mode_switch,  pin_is_u, pin_is_res, pin_is_mode_switch)
//                      so, si,sup,su,sms,iu, ir,ims

Application::Application()
	: q_set(7, 9, 1, 0, 37, 7, 47, 49),
	  p_set(6, 8, 6, 5, 35, 4, 45, 51),
	  parSet(5, 10, 3, 2, 24, 2, 26, 28, 53, ControlledPinMode::Voltage, ControlledPinMode::Voltage),
	  error(33,0,2,false),
	  release(31,0,2,true)
{
}

void Application::initialize()
{

	analogReadResolution(12);
	analogWriteResolution(12);

	q_set.begin();
	p_set.begin();
	parSet.begin();

	error.init();
	release.init();

	delay(1000);

	// Initialize display at last to wait until its ready
	disp_man.initialize();
}

void Application::loop(unsigned long loopCount)
{
	if(disp_man.getControlMode() == ControlMode::AnalogInputs){
		q_set.update();
		p_set.update();
		parSet.update();
	}

	q_set.measure();
	p_set.measure();
	parSet.measure();

	error.update();
	//release.update();

	disp_man.set_q_set(q_set.getSetVal());
	disp_man.set_q_is(q_set.getIsVal());
	disp_man.set_p_set(p_set.getSetVal());
	disp_man.set_p_is(p_set.getIsVal());
	disp_man.set_ps_pre_set(parSet.getSetValIn());
	disp_man.set_ps_set(parSet.getSetVal());
	disp_man.set_error(error.getState() == HIGH,error.hasNewValue());
	disp_man.set_release(release.getState() == HIGH,release.hasNewValue());

	disp_man.set_u_pre_adc_raw(p_set.getUPreAdcRaw());
	disp_man.set_u_adc_raw(p_set.getUAdcRaw());

	rkp::PhysicalValue tmp;

	switch (disp_man.getTouchEvent())
	{
	case TouchEvent::q_set_mode_change:
		q_set.setSetMode(CPM_NEXT(q_set.getSetMode()));
		break;
	case TouchEvent::p_set_mode_change:
		p_set.setSetMode(CPM_NEXT(p_set.getSetMode()));
		break;
	case TouchEvent::q_is_mode_change:
		q_set.setIsMode(CPM_NEXT(q_set.getIsMode()));
		break;
	case TouchEvent::p_is_mode_change:
		p_set.setIsMode(CPM_NEXT(p_set.getIsMode()));
		break;
	case TouchEvent::mem_q_tgl:
		q_set.setSetVal(mem_q);
		tmp = mem_q;
		mem_q = last_q;
		last_q = tmp;
		break;
	case TouchEvent::mem_p_tgl:
		p_set.setSetVal(mem_p);
		tmp = mem_p;
		mem_p = last_p;
		last_p = tmp;
		break;
	case TouchEvent::mem_ps_tgl:
		parSet.setSetVal(mem_ps);
		tmp = mem_ps;
		mem_ps = last_ps;
		last_ps = tmp;
		break;

	case TouchEvent::ps_val_1:
		parSet.setSetVal(PhysicalValue::directVolt(100));
		break;
	case TouchEvent::ps_val_2:
		parSet.setSetVal(PhysicalValue::directVolt(200));
		break;
	case TouchEvent::ps_val_3:
		parSet.setSetVal(PhysicalValue::directVolt(300));
		break;
	case TouchEvent::ps_val_4:
		parSet.setSetVal(PhysicalValue::directVolt(400));
		break;
	case TouchEvent::ps_val_5:
		parSet.setSetVal(PhysicalValue::directVolt(500));
		break;
	case TouchEvent::ps_val_6:
		parSet.setSetVal(PhysicalValue::directVolt(600));
		break;
	case TouchEvent::ps_val_7:
		parSet.setSetVal(PhysicalValue::directVolt(700));
		break;
	case TouchEvent::ps_val_8:
		parSet.setSetVal(PhysicalValue::directVolt(800));
		break;
	case TouchEvent::ps_val_9:
		parSet.setSetVal(PhysicalValue::directVolt(900));
		break;

	case TouchEvent::bar_graph_q:
		TRACELN("app bar graph change received");
		last_q = disp_man.getBarValue();
		q_set.setSetVal(last_q);
		TRACE("app bar graph change processed - num=");
		TRACELN((int)last_q.value);
		break;
	case TouchEvent::bar_graph_p:
		last_p = disp_man.getBarValue();
		p_set.setSetVal(last_p);
		break;
	case TouchEvent::bar_graph_ps:
		last_ps = disp_man.getBarValue();
		parSet.setSetVal(last_ps);
		break;
	case TouchEvent::release_on:
		release.setState(1,true);
		break;
	case TouchEvent::release_off:
		release.setState(0,true);
		break;
	case TouchEvent::release_toggle:
		release.setState((release.getState() == HIGH ? LOW : HIGH),true);
		break;
		
	default:
		break;
	}

	disp_man.loop(loopCount);

	delay(1);
}
#endif
