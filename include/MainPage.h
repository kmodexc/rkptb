#pragma once

#include "Page.h"
#include "pindefs.h"
#include "helpers.h"

class MainPage : public Page
{
	//variables
	public:
	protected:
	private:

	// Display texts for live values
	DisplayText dt_q;
	DisplayText dt_p;
	DisplayText dt_ps;

	// values of bargraphs in case of pages change
	uint8_t q_val;
	uint8_t p_val;
	uint8_t ps_val;

	// digits before comma
	uint8_t dig_bef_com;
	
	//functions
	public:

	// Constructors
	MainPage();
	~MainPage();
	
	// Initialization
	void initialize(Graphics*);

    void repaint(Graphics*);
	
	// Setter for live values
	void set_q_set(_float val,Unit un);
	void set_q_is(_float val,Unit un);
	void set_p_set(_float val,Unit un);
	void set_p_is(_float val,Unit un);
	void set_ps_pre_set(_float val,Unit un);
	void set_ps_set(_float val,Unit un);

	virtual TouchEvent getTouchEvent() override;
	virtual uint8_t getTouchValue() override;

	uint8_t getQBarVal() const;
	uint8_t getPBarval() const;

	void setDigBefCom(uint8_t);	
	uint8_t getDigBefCom();


	// Update loop
	void loop(uint64_t loopCount,Graphics*);
	
	
	protected:
	private:

}; //DisplayManager

