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
keyDispMode(-1)
{
	//q_set.setDisplayMode(Raw);
	//p_set.setDisplayMode(Raw);
	parSet.setDisplayMode(OldNewVal);
}

void Application::initialize() {
	// Due has only Default mode. The AREF pin is set manually
	//analogReference(EXTERNAL);

	analogReadResolution(12);
	analogWriteResolution(12);

	keyDispMode.begin();

	// output pins initialisieren
	q_set.begin();
	p_set.begin();
	parSet.begin();

	Wire.begin();

	stat.x = 100;
	stat.y = 100;
	stat.drawCharwise = true;
	disp.clearStr(stat.new_str, 15);


	p_setVal.x = 100;
	p_setVal.y = 140;
	p_setVal.drawCharwise = true;
	disp.clearStr(p_setVal.new_str, 6);

	p_setMode.x = 200;
	p_setMode.y = 140;
	p_setMode.drawCharwise = true;
	disp.clearStr(p_setMode.new_str, 3);

	p_isVal.x = 300;
	p_isVal.y = 140;
	p_isVal.drawCharwise = true;
	disp.clearStr(p_isVal.new_str, 6);

	p_isMode.x = 400;
	p_isMode.y = 140;
	p_isMode.drawCharwise = true;
	disp.clearStr(p_isMode.new_str, 3);


	q_setVal.x = 100;
	q_setVal.y = 180;
	q_setVal.drawCharwise = true;
	disp.clearStr(q_setVal.new_str, 6);

	q_setMode.x = 200;
	q_setMode.y = 180;
	q_setMode.drawCharwise = true;
	disp.clearStr(q_setMode.new_str, 3);

	q_isVal.x = 300;
	q_isVal.y = 180;
	q_isVal.drawCharwise = true;
	disp.clearStr(q_isVal.new_str, 6);

	q_isMode.x = 400;
	q_isMode.y = 180;
	q_isMode.drawCharwise = true;
	disp.clearStr(q_isMode.new_str, 3);


	ps_setVal.x = 100;
	ps_setVal.y = 220;
	ps_setVal.drawCharwise = true;
	disp.clearStr(ps_setVal.new_str, 6);

	ps_isVal.x = 300;
	ps_isVal.y = 220;
	ps_isVal.drawCharwise = true;
	disp.clearStr(ps_isVal.new_str, 6);



	delay(1000);

	disp.initialize();
	disp.command("#TA");
	disp.command("#ZF6");
	disp.command("#DL");
}

void Application::loop(unsigned long loopCount) {
	// update Values of output
	q_set.update();
	p_set.update();
	parSet.update();
	disp.loop(loopCount);

	if (keyDispMode.wasPressed()) {
		DisplayMode mode = q_set.getDisplayMode();
		if (mode == Normal) mode = Raw;
		else if (mode == Raw) mode = Direct;
		else mode = Normal;
		q_set.setDisplayMode(mode);
		p_set.setDisplayMode(mode);
		parSet.setDisplayMode(mode);
	}


	if (loopCount % 10 == 0)
	{

		bool error = !digitalRead(PIN_ERROR);


		// Release is the Release on the RKP. No Release means Fail-Save Condition.
		// U > 8,5V means Enable; U < 6,5V means Fail-Save
		bool mrel = !digitalRead(PIN_RELEASE);

		// Zeige Ist werte auf dem Display

		disp.clearStr(stat.new_str, 15);

		if (error)
		{
			static char errStr[] = "ERROR";
			for (int32_t cnt = 0; cnt < sizeof(errStr) - 1; cnt++){
				stat.new_str[cnt] = errStr[cnt];
			}
			stat.update = true;
			
		}
		else if(stat.old_str[0] == 'E'){
			stat.update = true;
		}



		if (mrel)
		{
			static char failsafeStr[] = "SAFE";
			for (int32_t cnt = 0; cnt < sizeof(failsafeStr) - 1; cnt++)
			{
				stat.new_str[9 + cnt] = failsafeStr[cnt];
			}
			stat.update = true;
		}
		else if(stat.old_str[9] == 'S'){
			stat.update = true;
		}



		//Zeige aktuellen Pwert
		q_set.show(q_setVal.new_str, q_setMode.new_str, q_isVal.new_str, q_isMode.new_str);

		q_setVal.update = true;
		q_setMode.update = true;
		q_isVal.update = true;
		q_isMode.update = true;

		//Zeige aktuellen Qwert
		p_set.show(p_setVal.new_str, p_setMode.new_str, p_isVal.new_str, p_isMode.new_str);

		p_setVal.update = true;
		p_setMode.update = true;
		p_isVal.update = true;
		p_isMode.update = true;


		//Zeige aktuellen ParameterSatz Wert
		parSet.show(ps_setVal.new_str, 0, ps_isVal.new_str, 0);


		ps_setVal.update = true;
		ps_isVal.update = true;

	}
	
	uint32_t NUM_FACTOR_DISPLAY_LOOP_WAIT = 1L;

	if ((loopCount + 0) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&stat);
	if ((loopCount + 5*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&q_setVal);
	if ((loopCount + 15*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&q_setMode);
	if ((loopCount + 25*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&q_isVal);
	if ((loopCount + 35*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&q_isMode);
	if ((loopCount + 45*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&p_setVal);
	if ((loopCount + 55*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&p_setMode);	
	if ((loopCount + 65*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&p_isVal);
	if ((loopCount + 75*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&p_isMode);
	if ((loopCount + 85*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&ps_setVal);
	if ((loopCount + 95*NUM_FACTOR_DISPLAY_LOOP_WAIT) % 100*NUM_FACTOR_DISPLAY_LOOP_WAIT)
	disp.text(&ps_isVal);

}
#endif
