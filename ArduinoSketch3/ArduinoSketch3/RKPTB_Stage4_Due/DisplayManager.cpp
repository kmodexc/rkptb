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
	disp.cpystr(dt_q.new_str,"Menge :");
	
	dt_p.drawCharwise = true;
	dt_p.x = 100;
	dt_p.y = 150;
	disp.clearStr(dt_p.new_str,DisplayText::STRLEN);
	disp.cpystr(dt_p.new_str,"Druck :");
	
	dt_ps.drawCharwise = true;
	dt_ps.x = 100;
	dt_ps.y = 200;
	disp.clearStr(dt_ps.new_str,DisplayText::STRLEN);
	disp.cpystr(dt_ps.new_str,"Param-set:");
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

void DisplayManager::loop(uint64_t loopCount)
{
	bool drawn_this_iter = false;
	
	if(!drawn_this_iter && ((loopCount/5) % 3) == 0){
		drawn_this_iter = disp.text(&dt_q,1);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 1) % 3) == 0){
		drawn_this_iter = disp.text(&dt_p,1);
	}
	
	if(!drawn_this_iter && (((loopCount/5) + 2) % 3) == 0){
		drawn_this_iter = disp.text(&dt_ps,1);
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
