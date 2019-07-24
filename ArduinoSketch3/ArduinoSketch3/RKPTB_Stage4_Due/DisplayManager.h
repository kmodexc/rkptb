/* 
* DisplayManager.h
*
* Created: 24.07.2019 15:58:38
* Author: Marius
*/


#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

#include "_float.h"
#include "Display.h"


enum Unit{
	Volt,
	MilliAmps
};


class DisplayManager
{
//variables
public:
protected:
private:

	// Display
	Display disp;

	// Display texts for live values
	DisplayText dt_q;
	DisplayText dt_p;
	DisplayText dt_ps;

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
	
	
	// Update loop
	void loop(uint64_t loopCount);
	
	// Static helpers for Unit
	void unit_print(char* str,Unit u);
	
	
protected:
private:

}; //DisplayManager

#endif //__DISPLAYMANAGER_H__
