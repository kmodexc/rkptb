#pragma once

#include "Page.h"
#include "pindefs.h"
#include "helpers.h"
#include "NumberPage.h"

enum MainPageMode{
	MPM_Normal,
	MPM_Numpad_Q,
	MPM_Numpad_P,
	MPM_Numpad_PS
};

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

	uint8_t mem_q_val;
	uint8_t mem_p_val;
	uint8_t mem_ps_val;

	bool update_q;
	bool update_p;
	bool update_ps;

	// digits before comma
	uint8_t dig_bef_com;

	NumberPage numberPage;
	
	MainPageMode mpmode;

	uint8_t td[TOUCH_EVENT_DATA_SIZE];

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
	virtual uint8_t *getTouchData() override;

	void setDigBefCom(uint8_t);	
	uint8_t getDigBefCom();

	// Update loop
	void loop(uint64_t loopCount,Graphics*);
	
	
	protected:
	private:

}; //DisplayManager

