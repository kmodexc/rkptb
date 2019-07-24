/* 
* DisplayManager.h
*
* Created: 24.07.2019 15:58:38
* Author: Marius
*/


#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__


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

	// Display texts for live values
	DisplayText dt_q;
	DisplayText dt_p;
	DisplayText dt_ps;

//functions
public:

	// Constructors
	DisplayManager();
	~DisplayManager();
	
	// Setter for live values
	
	
	
protected:
private:

}; //DisplayManager

#endif //__DISPLAYMANAGER_H__
