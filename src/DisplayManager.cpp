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

	disp.command("#TA");   // terminal off
	disp.command("#ZF6,"); // text font (6)
	disp.command("#DL");   // clear display
	disp.command("#AQ1,"); // send bar graph value after each setting
	disp.flush();

	// initialize pages
	mainPage.initialize(&disp);
	menuPage.initialize(&disp);
	currentPage.initialize(&disp);

	// set active page
	activePage = &mainPage;

	// paint active page
	activePage->repaint(&disp);
}

void DisplayManager::set_q_set(_float val, Unit un)
{
	activePage->set_q_set(val, un);
}

void DisplayManager::set_q_is(_float val, Unit un)
{
	activePage->set_q_is(val, un);
}

void DisplayManager::set_p_set(_float val, Unit un)
{
	activePage->set_p_set(val, un);
}

void DisplayManager::set_p_is(_float val, Unit un)
{
	activePage->set_p_is(val, un);
}

void DisplayManager::set_ps_pre_set(_float val, Unit un)
{
	activePage->set_ps_pre_set(val, un);
}

void DisplayManager::set_ps_set(_float val, Unit un)
{
	activePage->set_ps_set(val, un);
}

void DisplayManager::set_u_adc_raw(uint32_t val)
{
	if (activePage != &currentPage)
	{
		return;
	}
	currentPage.set_u_adc_raw(val);
}

void DisplayManager::set_u_pre_adc_raw(uint32_t val)
{
	if (activePage != &currentPage)
	{
		return;
	}
	currentPage.set_upre_adc_raw(val);
}

TouchEvent DisplayManager::getTouchEvent()
{
	TouchEvent ev = touchEvent;
	touchEvent = nothing;
	return ev;
}

uint8_t DisplayManager::getBarValue()
{
	return touchVal;
}

void DisplayManager::loop(uint64_t loopCount)
{
	activePage->loop(loopCount, &disp);

	disp.loop(loopCount);

	if (loopCount % 10 == 0)
	{
		// process events
		TouchEvent ev = activePage->getTouchEvent();
		switch (ev)
		{
		case menu_page_back:
			activePage = &mainPage;
			Sleep(100);
			activePage->repaint(&disp);
			Sleep(100);
			break;
		case go_menu_page:
			activePage = &menuPage;
			Sleep(100);
			activePage->repaint(&disp);
			Sleep(100);
			break;
		case precision_toggle:
			if (mainPage.getDigBefCom() >= 2)
			{
				mainPage.setDigBefCom(1);
			}
			else
			{
				mainPage.setDigBefCom(2);
			}
			break;
		case go_current_page:
			activePage = &currentPage;
			Sleep(100);
			activePage->repaint(&disp);
			Sleep(100);
			break;
		default:
			if (touchEvent == nothing)
			{
				touchEvent = ev;
				touchVal = activePage->getTouchValue();
			}
		}
	}
}
