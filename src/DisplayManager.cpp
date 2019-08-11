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

	// initialize pages
	mainPage.initialize(&disp);
	menuPage.initialize(&disp);
	currentPage.initialize(&disp);
	aboutPage.initialize(&disp);
	analogPage.initialize(&disp);
	numberPage.initialize(&disp);

	// set active page
	activePage = &numberPage;

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

ControlMode DisplayManager::getControlMode()
{
	if (activePage == &analogPage)
	{
		return AnalogInputs;
	}
	return TouchScreen;
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
			activePage->unshow(&disp);
			activePage = &mainPage;
			Sleep(10);
			activePage->repaint(&disp);
			Sleep(10);
			break;
		case go_menu_page:
			activePage->unshow(&disp);
			activePage = &menuPage;
			Sleep(10);
			activePage->repaint(&disp);
			Sleep(10);
			break;
		case precision_toggle:
			if (mainPage.getDigBefCom() >= 2)
			{
				mainPage.setDigBefCom(1);
				analogPage.setDigBefCom(1);
			}
			else
			{
				mainPage.setDigBefCom(2);
				analogPage.setDigBefCom(2);
			}
			break;
		case go_current_page:
			activePage->unshow(&disp);
			activePage = &currentPage;
			Sleep(10);
			activePage->repaint(&disp);
			Sleep(10);
			break;
		case go_about_page:
			activePage->unshow(&disp);
			activePage = &aboutPage;
			Sleep(10);
			activePage->repaint(&disp);
			Sleep(10);
			break;
		case go_analog_page:
			activePage->unshow(&disp);
			activePage = &analogPage;
			Sleep(10);
			activePage->repaint(&disp);
			Sleep(10);
			break;
		case go_number_page:
			activePage->unshow(&disp);
			activePage = &numberPage;
			Sleep(10);
			activePage->repaint(&disp);
			Sleep(10);
			break;
		default:
			if (touchEvent == nothing)
			{
				touchEvent = ev;
				touchVal = activePage->getTouchData()[0];
			}
		}
	}
}
