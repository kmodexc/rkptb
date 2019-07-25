/*
* DisplayManager.cpp
*
* Created: 24.07.2019 15:58:37
* Author: Marius
*/


#include "DisplayManager.h"

// default constructor
DisplayManager::DisplayManager()
{
	dt_q.drawCharwise = true;
	dt_q.x = 100;
	dt_q.y = 100;
	disp.clearStr(dt_q.new_str,DisplayText::STRLEN);
	disp.clearStr(dt_q.old_str,DisplayText::STRLEN);
	disp.cpystr(dt_q.new_str,"Menge :");
	
	dt_p.drawCharwise = true;
	dt_p.x = 100;
	dt_p.y = 150;
	disp.clearStr(dt_p.new_str,DisplayText::STRLEN);
	disp.clearStr(dt_p.old_str,DisplayText::STRLEN);
	disp.cpystr(dt_p.new_str,"Druck :");
	
	dt_ps.drawCharwise = true;
	dt_ps.x = 100;
	dt_ps.y = 200;
	disp.clearStr(dt_ps.new_str,DisplayText::STRLEN);
	disp.clearStr(dt_ps.old_str,DisplayText::STRLEN);
	disp.cpystr(dt_ps.new_str,"Param :");
	
	
	// init receive buffer
	for(size_t cnt=0;cnt < DISPM_REC_BUFFER_SIZE; cnt++){
		rec_buffer[cnt] = 0;
	}
	// init touch event
	te = nothing;
} //DisplayManager

// default destructor
DisplayManager::~DisplayManager()
{
} //~DisplayManager

void DisplayManager::initialize()
{
	disp.initialize();
	disp.command("#TA");
	disp.command("#ZF6");
	disp.command("#DL");
	
	disp.command("#AT100,300,200,350,1,0,qset\x0d");
	disp.command("#AT100,375,200,425,2,0,pset\x0d");
	disp.command("#AT300,300,400,350,3,0,qis\x0d");
	disp.command("#AT300,375,400,425,4,0,pis\x0d");
}

void DisplayManager::set_q_set(_float val,Unit un)
{
	val.print(dt_q.new_str+10);
	unit_print(dt_q.new_str+16,un);
	dt_q.update = true;
}

void DisplayManager::set_q_is(_float val,Unit un)
{
	val.print(dt_q.new_str+20);
	unit_print(dt_q.new_str+26,un);
	dt_q.update = true;
}

void DisplayManager::set_p_set(_float val,Unit un)
{
	val.print(dt_p.new_str+10);
	unit_print(dt_p.new_str+16,un);
	dt_p.update = true;
}

void DisplayManager::set_p_is(_float val,Unit un)
{
	val.print(dt_p.new_str+20);
	unit_print(dt_p.new_str+26,un);
	dt_p.update = true;
}

void DisplayManager::set_ps_pre_set(_float val,Unit un)
{
	val.print(dt_ps.new_str+20);
	unit_print(dt_ps.new_str+26,un);
	dt_ps.update = true;
}

void DisplayManager::set_ps_set(_float val,Unit un)
{
	val.print(dt_ps.new_str+10);
	unit_print(dt_ps.new_str+16,un);
	dt_ps.update = true;
}

TouchEvent DisplayManager::getTouchEvent()
{
	TouchEvent ret_ev = te;
	te = nothing;
	return ret_ev;
}

void DisplayManager::readSendBuffer()
{
	if(te == nothing && disp.requestBuffer(rec_buffer,4)){
		switch(rec_buffer[3]){
			case 1:
			te = q_set_mode_change;
			break;
			case 2:
			te = p_set_mode_change;
			break;
			case 3:
			te = q_is_mode_change;
			break;
			case 4:
			te = p_is_mode_change;
			break;
			default:
			TRACELN(rec_buffer[3]);
			break;
		}
	}
}

void DisplayManager::loop(uint64_t loopCount)
{
	bool drawn_this_iter = false;
	
	if(!drawn_this_iter && ((loopCount/5) % 4) == 0){
		drawn_this_iter = disp.text(&dt_q,1);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 1) % 4) == 0){
		drawn_this_iter = disp.text(&dt_p,1);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 2) % 4) == 0){
		drawn_this_iter = disp.text(&dt_ps,1);
	}
	
	if(!drawn_this_iter && (loopCount % 100) == 0){
		drawn_this_iter = true;
		readSendBuffer();
	}
	
	disp.loop(loopCount);
}

void DisplayManager::unit_print(char* str,Unit u)
{
	if (u == Unit::Volt) {
		str[0] = 'V';
		str[1] = ' ';
	}
	else {
		str[0] = 'm';
		str[1] = 'A';
	}
}
