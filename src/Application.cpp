#ifndef _APPLICATION_CPP_
#define _APPLICATION_CPP_

#include "Application.h"

//CControlledOutput Constructor sets pins for the Output
//(pin_set_out, pin_set_in,  pin_set_u_pre,  pin_set_u,  pin_set_mode_switch,  pin_is_u, pin_is_res, pin_is_mode_switch)
//                      so, si,sup,su,sms,iu, ir,ims

Application::Application()
	: q_set(7, 9, 1, 0, 37, 7, 47, 49),
	  p_set(6, 8, 6, 5, 35, 4, 45, 51),
	  parSet(5, 10, 3, 2, 24, 2, 26, 28, 53, Voltage, Voltage),
	  mem_q(0),
	  mem_p(0),
	  last_q(0),
	  last_p(0)
{
	//q_set.setDisplayMode(Raw);
	//p_set.setDisplayMode(Raw);
	parSet.setDisplayMode(OldNewVal);
}

void Application::initialize()
{

	analogReadResolution(12);
	analogWriteResolution(12);

	q_set.begin();
	p_set.begin();
	parSet.begin();

	delay(1000);

	// Initialize display at last to wait until its ready
	disp_man.initialize();
}

void Application::loop(unsigned long loopCount)
{

	//bool error = !digitalRead(PIN_ERROR);
	//bool mrel = !digitalRead(PIN_RELEASE);

	q_set.measure();
	p_set.measure();
	parSet.measure();

	disp_man.set_q_set(q_set.getSetVal(), (Unit)q_set.getSetMode());
	disp_man.set_q_is(q_set.getIsVal(), (Unit)q_set.getIsMode());
	disp_man.set_p_set(p_set.getSetVal(), (Unit)p_set.getSetMode());
	disp_man.set_p_is(p_set.getIsVal(), (Unit)p_set.getIsMode());
	disp_man.set_ps_set(parSet.getSetVal(), (Unit)parSet.getSetMode());

	disp_man.set_u_pre_adc_raw(p_set.getUPreAdcRaw());
	disp_man.set_u_adc_raw(p_set.getUAdcRaw());

	_float tmp;

	switch (disp_man.getTouchEvent())
	{
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
	case mem_q_tgl:
		q_set.setSetVal(mem_q);
		tmp = mem_q;
		mem_q = last_q;
		last_q = tmp;
		break;
	case mem_p_tgl:
		p_set.setSetVal(mem_p);
		tmp = mem_p;
		mem_p = last_p;
		last_p = tmp;
		break;
	case mem_ps_tgl:
		parSet.setSetVal(mem_ps);
		tmp = mem_ps;
		mem_ps = last_ps;
		last_ps = tmp;
		break;

	case ps_val_1:
		parSet.setSetVal(_float::direct(100));
		break;
	case ps_val_2:
		parSet.setSetVal(_float::direct(200));
		break;
	case ps_val_3:
		parSet.setSetVal(_float::direct(300));
		break;
	case ps_val_4:
		parSet.setSetVal(_float::direct(400));
		break;
	case ps_val_5:
		parSet.setSetVal(_float::direct(500));
		break;
	case ps_val_6:
		parSet.setSetVal(_float::direct(600));
		break;
	case ps_val_7:
		parSet.setSetVal(_float::direct(700));
		break;
	case ps_val_8:
		parSet.setSetVal(_float::direct(800));
		break;
	case ps_val_9:
		parSet.setSetVal(_float::direct(900));
		break;

	case bar_graph_q:
		last_q = _float::direct(11 * disp_man.getBarValue());
		q_set.setSetVal(last_q);
		break;
	case bar_graph_p:
		last_p = _float::direct(11 * disp_man.getBarValue());
		p_set.setSetVal(last_p);
		break;
	case bar_graph_ps:
		last_ps = _float::direct(11 * disp_man.getBarValue());
		parSet.setSetVal(last_ps);
		break;

	default:
		break;
	}

	disp_man.loop(loopCount);

	delay(1);
}
#endif
