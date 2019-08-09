/*
* DisplayManager.h
*
* Created: 24.07.2019 15:58:38
* Author: Marius
*/


#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

#include "Display.h"

#include "MainPage.h"
#include "MenuPage.h"
#include "CurrentPage.h"
#include "AboutPage.h"
#include "AnalogPage.h"


class DisplayManager
{
	//variables
	public:
	protected:
	private:

	// Display
	Display disp;


	MainPage mainPage;
	MenuPage menuPage;
	CurrentPage currentPage;
	AboutPage aboutPage;
	AnalogPage analogPage;

	Page* activePage;

	TouchEvent touchEvent;
	uint8_t touchVal;

	//functions
	public:

	// Constructors
	DisplayManager();
	~DisplayManager();
	
	// Initialization
	void initialize();
	
	// Setter for live values
	void set_q_set(_float val,Unit un);
	void set_q_is(_float val,Unit un);
	void set_p_set(_float val,Unit un);
	void set_p_is(_float val,Unit un);
	void set_ps_pre_set(_float val,Unit un);
	void set_ps_set(_float val,Unit un);
	// for current page
	void set_u_adc_raw(uint32_t);
	void set_u_pre_adc_raw(uint32_t);
	
	// request function for touch events
	TouchEvent getTouchEvent();
	uint8_t getBarValue();

	// function to get control status for set-values
	ControlMode getControlMode(); 
	
	// Update loop
	void loop(uint64_t loopCount);
	
	protected:
	private:

}; //DisplayManager

#endif //__DISPLAYMANAGER_H__
