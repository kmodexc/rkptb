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
	
} //DisplayManager

// default destructor
DisplayManager::~DisplayManager()
{
} //~DisplayManager

void DisplayManager::initialize()
{
	// initialize display first
	disp.initialize();
	
	
	// display settings
	
	disp.command("#TA");	// terminal off
	disp.command("#ZF6,");	// text font (6)
	disp.command("#DL");	// clear display
	disp.command("#AQ1,");	// send bar graph value after each setting
	disp.flush();


	// initialize pages
	mainPage.initialize(&disp);


	// set active page
	activePage = &mainPage;
	

	// paint active page
	activePage->repaint(&disp);
}

void DisplayManager::set_q_set(_float val,Unit un)
{
	activePage->set_q_set(val,un);
}

void DisplayManager::set_q_is(_float val,Unit un)
{
	activePage->set_q_is(val,un);
}

void DisplayManager::set_p_set(_float val,Unit un)
{
	activePage->set_p_set(val,un);
}

void DisplayManager::set_p_is(_float val,Unit un)
{
	activePage->set_p_is(val,un);
}

void DisplayManager::set_ps_pre_set(_float val,Unit un)
{
	activePage->set_ps_pre_set(val,un);
}

void DisplayManager::set_ps_set(_float val,Unit un)
{
	activePage->set_ps_set(val,un);
}

TouchEvent DisplayManager::getTouchEvent()
{
	return activePage->getTouchEvent();
}

uint8_t DisplayManager::getBarValue()
{
	return activePage->getTouchValue();
}

void DisplayManager::loop(uint64_t loopCount)
{
	activePage->loop(loopCount,&disp);
	
	disp.loop(loopCount);
}


