#pragma once

#include "NumberPage.h"
#include "Page.h"
#include "helpers.h"
#include "pindefs.h"
#include "ControlledPinMode.h"
#include "Bargraph.h"

enum class MainPageMode
{
	Normal,
	Numpad_Q,
	Numpad_P,
	Numpad_PS
};

struct ContOpBaGrSet{
	DisplayText dispTex;
	RKP::Bargraph bg;
	_float mem;
	ControlledPinMode mode;
	ContOpBaGrSet(size_t x,size_t y,uint8_t code, const char* label)
		:bg(x,y,code,label){}
};

class MainPage : public Page
{
	//variables
public:
protected:
private:
	ContOpBaGrSet mQ;
	ContOpBaGrSet mP;
	ContOpBaGrSet mPS;

	// digits before comma
	uint8_t dig_bef_com;

	NumberPage numberPage;

	MainPageMode mpmode;

	uint8_t touchDataBuffer[TOUCH_EVENT_DATA_SIZE];
	uint8_t *touchDataPtr;

	//functions
public:
	// Constructors
	MainPage();
	~MainPage();

	// Initialization
	void initialize(Graphics *);

	void repaint(Graphics *);

	// Setter for live values
	void set_q_set(_float val, Unit un);
	void set_q_is(_float val, Unit un);
	void set_p_set(_float val, Unit un);
	void set_p_is(_float val, Unit un);
	void set_ps_pre_set(_float val, Unit un);
	void set_ps_set(_float val, Unit un);

	virtual TouchEvent getTouchEvent() override;
	virtual uint8_t *getTouchData() override;

	void setDigBefCom(uint8_t);
	uint8_t getDigBefCom();

	// Update loop
	void loop(uint64_t loopCount, Graphics *);

protected:
private:
	static uint8_t voltToBgVal(const _float &f);
	static _float bgValToVolt(uint8_t v);

	_float numpadEnterHandler(ContOpBaGrSet*);
	void bargraphChangeEventHandler(ContOpBaGrSet*);
	void memTglEventHandler(ContOpBaGrSet*);
	void measureModeChangeHandler(ContOpBaGrSet*);

}; //DisplayManager
