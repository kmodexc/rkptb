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
	val.print(dt_q.new_str);
	unit_print(dt_q.new_str+6,un);
	dt_q.update = true;
	disp.text(&dt_q);
}

void DisplayManager::loop(uint64_t loopCount)
{
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
