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

double DisplayManager::getBarValue()
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
		case go_menu_page:
		case go_current_page:
		case go_about_page:
		case go_analog_page:
		case go_number_page:
			activePage->unshow(&disp);
			switch (ev)
			{
			case menu_page_back:
				activePage = &mainPage;
				break;
			case go_menu_page:
				activePage = &menuPage;
				break;
			case go_current_page:
				activePage = &currentPage;
				break;
			case go_about_page:
				activePage = &aboutPage;
				break;
			case go_analog_page:
				activePage = &analogPage;
				break;
			case go_number_page:
				activePage = &numberPage;
				break;
			default:
				break;
			}
			activePage->repaint(&disp);
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
		case bar_graph_q:
			TRACELN("bar graph change");
		default:
			if (touchEvent == nothing)
			{
				touchEvent = ev;
				touchVal = *((double*)activePage->getTouchData());
			}
			else{
				TRACELN("Event discarded");
			}
		}
	}
}
