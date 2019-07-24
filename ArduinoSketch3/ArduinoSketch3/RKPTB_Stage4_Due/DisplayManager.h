/* 
* DisplayManager.h
*
* Created: 24.07.2019 14:47:24
* Author: Marius
*/


#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

enum Unit { Volts , MilliAmps };

class DisplayManager
{
//variables
public:
protected:
private:

//functions
public:

	// Constructor
	DisplayManager();
	~DisplayManager();
	
	// Setter to give information to display
	void set_q_set(uint32_t qs, Unit u);
	void set_p_set(uint32_t ps, Unit u);
	void set_q_is(uint32_t qi, Unit u);
	void set_p_is(uint32_t pi, Unit u);
	void set_ps_pre_set(uint32_t psps, Unit u);
	void set_ps_set(uint32_t pss, Unit u);

	// Update method
	void update(uint64_t loopCount);

protected:
private:

}; //DisplayManager

#endif //__DISPLAYMANAGER_H__
