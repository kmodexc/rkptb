#include "MainPage.h"

using namespace rkp;

// default constructor
MainPage::MainPage()
	:mQ(100,250,1,"Q"),
	mP(100,320,2,"P"),
	mPS(100,390,3,"PS")
{
	dig_bef_com = 1;

	mQ.mode = ControlledPinMode::Voltage;
	mP.mode = ControlledPinMode::Voltage;
	mPS.mode = ControlledPinMode::Voltage;

	mQ.dispTex.drawCharwise = true;
	mQ.dispTex.x = 100;
	mQ.dispTex.y = 100;
	rkp::clearStr(mQ.dispTex.new_str, DisplayText::STRLEN);
	rkp::cpystr(mQ.dispTex.new_str, "Menge :");

	mP.dispTex.drawCharwise = true;
	mP.dispTex.x = 100;
	mP.dispTex.y = 150;
	rkp::clearStr(mP.dispTex.new_str, DisplayText::STRLEN);
	rkp::cpystr(mP.dispTex.new_str, "Druck :");

	mPS.dispTex.drawCharwise = true;
	mPS.dispTex.x = 100;
	mPS.dispTex.y = 200;
	rkp::clearStr(mPS.dispTex.new_str, DisplayText::STRLEN);
	rkp::cpystr(mPS.dispTex.new_str, "Param :");

} //MainPage

// default destructor
MainPage::~MainPage()
{
} //~MainPage

void MainPage::initialize(Graphics *pg)
{
	Page::initialize(pg);
	numberPage.initialize(pg);
}

void MainPage::repaint(Graphics *pg)
{
	Page::repaint(pg);

	pg->clearScreen();

	pg->setButtonColor(BCNormal);
	pg->createButton(0, 0, 5, "Menu");

	pg->createButton(100, 0, 12, "FailS");

	pg->createButton(200, 0, 6, "MEM Q");
	pg->createButton(300, 0, 7, "MEM P");
	pg->createButton(400, 0, 8, "MEM PS");

	pg->createButton(500, 0, 9, "SET Q");
	pg->createButton(600, 0, 10, "SET P");
	pg->createButton(700, 0, 11, "SET PS");

	// measurement mode switch buttons
	pg->setButtonColor(BCInvisible);
	pg->createButton(420, 100, 40, 20, 1, "");
	pg->createButton(420, 150, 40, 20, 2, "");
	pg->createButton(620, 100, 40, 20, 3, "");
	pg->createButton(620, 150, 40, 20, 4, "");

	// bar graphs
	mQ.bg.repaint(pg);
	mP.bg.repaint(pg);
	mPS.bg.repaint(pg);

	// reset str
	rkp::clearStr(mQ.dispTex.old_str, DisplayText::STRLEN);
	rkp::clearStr(mP.dispTex.old_str, DisplayText::STRLEN);
	rkp::clearStr(mPS.dispTex.old_str, DisplayText::STRLEN);
}

void MainPage::set_q_set(const PhysicalValue& val)
{
	val.value.print(mQ.dispTex.new_str + 10, dig_bef_com);
	rkp::unit_print(mQ.dispTex.new_str + 16, val.getUnit());
	mQ.dispTex.update = true;
}

void MainPage::set_q_is(const PhysicalValue& val)
{
	val.value.print(mQ.dispTex.new_str + 20, dig_bef_com);
	rkp::unit_print(mQ.dispTex.new_str + 26, val.getUnit());
	mQ.dispTex.update = true;
}

void MainPage::set_p_set(const PhysicalValue& val)
{
	val.value.print(mP.dispTex.new_str + 10, dig_bef_com);
	rkp::unit_print(mP.dispTex.new_str + 16, val.getUnit());
	mP.dispTex.update = true;
}

void MainPage::set_p_is(const PhysicalValue& val)
{
	val.value.print(mP.dispTex.new_str + 20, dig_bef_com);
	rkp::unit_print(mP.dispTex.new_str + 26, val.getUnit());
	mP.dispTex.update = true;
}

void MainPage::set_ps_pre_set(const PhysicalValue& val)
{
	// val.value.print(mPS.dispTex.new_str + 20, dig_bef_com);
	// rkp::unit_print(mPS.dispTex.new_str + 26, val.getUnit());
	// mPS.dispTex.update = true;
}

void MainPage::set_ps_set(const PhysicalValue& val)
{
	val.value.print(mPS.dispTex.new_str + 10, dig_bef_com);
	rkp::unit_print(mPS.dispTex.new_str + 16, val.getUnit());
	mPS.dispTex.update = true;
}

void MainPage::set_error(const bool val,const bool newVal){
	if(val){
		strcpy(mPS.dispTex.new_str + 20,"ERROR");
		mPS.dispTex.update = true;
	}else if(!val && newVal){
		strcpy(mPS.dispTex.new_str + 20,"     ");
		mPS.dispTex.update = true;
	}
}

void MainPage::set_release(const bool val,const bool newVal){
	if(!val){
		strcpy(mPS.dispTex.new_str + 20,"FAILSAFE");
		mPS.dispTex.update = true;
	}else if(val && newVal){
		strcpy(mPS.dispTex.new_str + 20,"        ");
		mPS.dispTex.update = true;
	}
}

TouchEvent MainPage::getTouchEvent()
{
	TouchEvent ev;
	if (mpmode == MainPageMode::Normal)
	{
		ev = Page::getTouchEvent();
		touchDataPtr = Page::getTouchData();
	}
	else
	{
		ev = numberPage.getTouchEvent();
		touchDataPtr = numberPage.getTouchData();
	}

	switch (ev)
	{
	case TouchEvent::nothing:
		break;
	case TouchEvent::bar_graph_q:
		bargraphChangeEventHandler(&mQ);
		break;
	case TouchEvent::bar_graph_p:
		bargraphChangeEventHandler(&mP);
		break;
	case TouchEvent::bar_graph_ps:
		bargraphChangeEventHandler(&mPS);
		break;
	case TouchEvent::mem_q_tgl:
		memTglEventHandler(&mQ);
		break;
	case TouchEvent::mem_p_tgl:
		memTglEventHandler(&mP);
		break;
	case TouchEvent::mem_ps_tgl:
		memTglEventHandler(&mPS);
		break;
	case TouchEvent::go_numpad_q:
		mpmode = MainPageMode::Numpad_Q;
		break;
	case TouchEvent::go_numpad_p:
		mpmode = MainPageMode::Numpad_P;
		break;
	case TouchEvent::go_numpad_ps:
		mpmode = MainPageMode::Numpad_PS;
		break;
	case TouchEvent::number_page_enter:
		if (mpmode == MainPageMode::Numpad_Q)
		{
			ev = TouchEvent::bar_graph_q;
			numpadEnterHandler(&mQ);
		}
		if (mpmode == MainPageMode::Numpad_P)
		{
			ev = TouchEvent::bar_graph_p;
			numpadEnterHandler(&mP);
		}
		if (mpmode == MainPageMode::Numpad_PS)
		{
			ev = TouchEvent::bar_graph_ps;
			numpadEnterHandler(&mPS);
		}
		mpmode = MainPageMode::Normal;
		break;
	case TouchEvent::q_set_mode_change:
		measureModeChangeHandler(&mQ);
		break;
	case TouchEvent::p_set_mode_change:
		measureModeChangeHandler(&mP);
		break;
	default:
		TRACE((int)ev);
		TRACELN("  unknown event forewarded");
		break;
	}
	return ev;
}

uint8_t *MainPage::getTouchData()
{
	return touchDataPtr;
}

void MainPage::setDigBefCom(uint8_t dbc)
{
	dig_bef_com = dbc;
	if (dig_bef_com == 1)
	{
		mQ.dispTex.new_str[14] = ' ';
		mP.dispTex.new_str[14] = ' ';
		mPS.dispTex.new_str[14] = ' ';
		mQ.dispTex.new_str[24] = ' ';
		mP.dispTex.new_str[24] = ' ';
		mPS.dispTex.new_str[24] = ' ';
	}
}

uint8_t MainPage::getDigBefCom()
{
	return dig_bef_com;
}

void MainPage::loop(uint64_t loopCount, Graphics *pg)
{
	bool drawn_this_iter = false;

	if (!numberPage.isVisible() &&
		(mpmode == MainPageMode::Numpad_Q || mpmode == MainPageMode::Numpad_P || mpmode == MainPageMode::Numpad_PS))
	{
		unshow(pg);
		numberPage.repaint(pg);
		drawn_this_iter = true;
	}

	if (numberPage.isVisible() && mpmode == MainPageMode::Normal)
	{
		numberPage.unshow(pg);
		repaint(pg);
		drawn_this_iter = true;
	}

	if (mpmode == MainPageMode::Normal)
	{
		if (!drawn_this_iter && ((loopCount / 5) % 4) == 0)
		{
			drawn_this_iter = pg->text(&mQ.dispTex);
		}

		if (!drawn_this_iter && (((loopCount / 5) + 1) % 4) == 0)
		{
			drawn_this_iter = pg->text(&mP.dispTex);
		}

		if (!drawn_this_iter && (((loopCount / 5) + 2) % 4) == 0)
		{
			drawn_this_iter = pg->text(&mPS.dispTex);
		}

		if(!drawn_this_iter && ((loopCount % 10) == 1)){
			drawn_this_iter = mQ.bg.loop(loopCount,pg);
		}

		if(!drawn_this_iter && ((loopCount % 10) == 2)){
			drawn_this_iter = mP.bg.loop(loopCount,pg);
		}

		if(!drawn_this_iter && ((loopCount % 10) == 3)){
			drawn_this_iter = mPS.bg.loop(loopCount,pg);
		}

		if (!drawn_this_iter && (((loopCount / 5) + 3) % 4) == 0 && ((loopCount % 5) == 0))
		{
			drawn_this_iter = true;
			Page::loop(loopCount, pg);
		}
	}

	if (!drawn_this_iter &&
		(mpmode == MainPageMode::Numpad_Q || mpmode == MainPageMode::Numpad_P || mpmode == MainPageMode::Numpad_PS))
	{
		numberPage.loop(loopCount, pg);
		drawn_this_iter = true;
	}
}

PhysicalValue MainPage::numpadEnterHandler(ContOpBaGrSet *cobg)
{
	PhysicalValue sendVal(numberPage.getValue(),cobg->mode == ControlledPinMode::Voltage ? Unit::Volt : Unit::MilliAmps);
	sendVal.serialize(touchDataBuffer, TOUCH_EVENT_DATA_SIZE);
	cobg->bg.setValue(sendVal.value);
	touchDataPtr = touchDataBuffer;
	TRACE("number page event processed - num =");
	sendVal.value.print((char *)touchDataBuffer + 10);
	touchDataBuffer[16] = 0;
	TRACELN((char *)touchDataBuffer + 10); 
	return sendVal;
}

void MainPage::bargraphChangeEventHandler(ContOpBaGrSet *cobg)
{
	cobg->bg.bargraphChangeEvent(TouchEvent::nothing,getTouchData());
	PhysicalValue val(cobg->bg.getValue(),cobg->mode == ControlledPinMode::Voltage ? Unit::Volt : Unit::MilliAmps);
	val.serialize(touchDataBuffer, TOUCH_EVENT_DATA_SIZE);
	TRACE("mainpage bargraph change processed - num=");
	TRACELN((int)cobg->bg.getValue());
	touchDataPtr = touchDataBuffer;
}

void MainPage::memTglEventHandler(ContOpBaGrSet *cobg)
{
	PhysicalValue tmp = cobg->mem;
	cobg->mem.value = cobg->bg.getValue();
	cobg->bg.setValue(tmp.value);
}

void MainPage::measureModeChangeHandler(ContOpBaGrSet *cobg)
{
	CPM_SWITCH(cobg->mode);
	switch (cobg->mode)
	{
	case ControlledPinMode::Current:
		cobg->bg.setRange(_float::direct(390), _float::direct(2100));
		break;
	default:
		cobg->bg.setRange(_float::direct(0), _float::direct(1100));
		break;
	}
}