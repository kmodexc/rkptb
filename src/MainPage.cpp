#include "MainPage.h"

// default constructor
MainPage::MainPage()
{
	dig_bef_com = 1;

	mem_q_val = 0;
	mem_p_val = 0;
	mem_ps_val = 0;

	update_q = false;
	update_p = false;
	update_ps = false;

	dt_q.drawCharwise = true;
	dt_q.x = 100;
	dt_q.y = 100;
	rkp::clearStr(dt_q.new_str, DisplayText::STRLEN);
	rkp::cpystr(dt_q.new_str, "Menge :");

	dt_p.drawCharwise = true;
	dt_p.x = 100;
	dt_p.y = 150;
	rkp::clearStr(dt_p.new_str, DisplayText::STRLEN);
	rkp::cpystr(dt_p.new_str, "Druck :");

	dt_ps.drawCharwise = true;
	dt_ps.x = 100;
	dt_ps.y = 200;
	rkp::clearStr(dt_ps.new_str, DisplayText::STRLEN);
	rkp::cpystr(dt_ps.new_str, "Param :");

} //MainPage

// default destructor
MainPage::~MainPage()
{
} //~MainPage

void MainPage::initialize(Graphics *pg)
{
	Page::initialize(pg);
}

void MainPage::repaint(Graphics *pg)
{
	pg->clearScreen();

	pg->setButtonColor(BCNormal);
	pg->createButton(0, 0, 5, "Menu");
	pg->createButton(200, 0, 6, "MEM Q");
	pg->createButton(300, 0, 7, "MEM P");
	pg->createButton(400, 0, 8, "MEM PS");

	// measurement mode switch buttons
	pg->setButtonColor(BCInvisible);
	pg->createButton(420, 100, 40, 20, 1, "");
	pg->createButton(420, 150, 40, 20, 2, "");
	pg->createButton(620, 100, 40, 20, 3, "");
	pg->createButton(620, 150, 40, 20, 4, "");

	// bar graphs
	pg->createBargraph(100,250,1,"Q");
	pg->setBargraphVal(1,q_val);
	pg->createBargraph(100,320,2,"P");
	pg->setBargraphVal(2,p_val);
	pg->createBargraph(100,390,3,"PS");
	pg->setBargraphVal(3,ps_val);

	// reset str
	rkp::clearStr(dt_q.old_str, DisplayText::STRLEN);
	rkp::clearStr(dt_p.old_str, DisplayText::STRLEN);
	rkp::clearStr(dt_ps.old_str, DisplayText::STRLEN);
}

void MainPage::set_q_set(_float val, Unit un)
{
	val.print(dt_q.new_str + 10, dig_bef_com);
	rkp::unit_print(dt_q.new_str + 16, un);
	dt_q.update = true;
}

void MainPage::set_q_is(_float val, Unit un)
{
	val.print(dt_q.new_str + 20, dig_bef_com);
	rkp::unit_print(dt_q.new_str + 26, un);
	dt_q.update = true;
}

void MainPage::set_p_set(_float val, Unit un)
{
	val.print(dt_p.new_str + 10, dig_bef_com);
	rkp::unit_print(dt_p.new_str + 16, un);
	dt_p.update = true;
}

void MainPage::set_p_is(_float val, Unit un)
{
	val.print(dt_p.new_str + 20, dig_bef_com);
	rkp::unit_print(dt_p.new_str + 26, un);
	dt_p.update = true;
}

void MainPage::set_ps_pre_set(_float val, Unit un)
{
	// val.print(dt_ps.new_str + 20, dig_bef_com);
	// rkp::unit_print(dt_ps.new_str + 26, un);
	// dt_ps.update = true;
}

void MainPage::set_ps_set(_float val, Unit un)
{
	val.print(dt_ps.new_str + 10, dig_bef_com);
	rkp::unit_print(dt_ps.new_str + 16, un);
	dt_ps.update = true;
}

TouchEvent MainPage::getTouchEvent()
{
	TouchEvent ev = Page::getTouchEvent();

	uint8_t tmp = 0;

	switch (ev)
	{
	case bar_graph_q:
		q_val = getTouchValue();
		break;
	case bar_graph_p:
		p_val = getTouchValue();
		break;
	case bar_graph_ps:
		ps_val = getTouchValue();
		break;
	case mem_q_tgl:
		tmp = mem_q_val;
		mem_q_val = q_val;
		q_val = tmp;
		update_q = true;;
		break;
	case mem_p_tgl:
		tmp = mem_p_val;
		mem_p_val = p_val;
		p_val = tmp;
		update_p = true;;
		break;
	case mem_ps_tgl:
		tmp = mem_ps_val;
		mem_ps_val = ps_val;
		ps_val = tmp;
		update_ps = true;;
		break;
	default:
		break;
	}
	return ev;
}

uint8_t MainPage::getTouchValue()
{
	return Page::getTouchValue();
}

void MainPage::setDigBefCom(uint8_t dbc)
{
	dig_bef_com = dbc;
	if (dig_bef_com == 1)
	{
		dt_q.new_str[14] = ' ';
		dt_p.new_str[14] = ' ';
		dt_ps.new_str[14] = ' ';
		dt_q.new_str[24] = ' ';
		dt_p.new_str[24] = ' ';
		dt_ps.new_str[24] = ' ';
	}
}

uint8_t MainPage::getDigBefCom()
{
	return dig_bef_com;
}

void MainPage::loop(uint64_t loopCount, Graphics *pg)
{
	bool drawn_this_iter = false;

	if (!drawn_this_iter && ((loopCount / 5) % 4) == 0)
	{
		drawn_this_iter = pg->text(&dt_q);
	}

	if (!drawn_this_iter && (((loopCount / 5) + 1) % 4) == 0)
	{
		drawn_this_iter = pg->text(&dt_p);
	}

	if (!drawn_this_iter && (((loopCount / 5) + 2) % 4) == 0)
	{
		drawn_this_iter = pg->text(&dt_ps);
	}

	if(!drawn_this_iter && update_q){
		pg->setBargraphVal(1,q_val);
		drawn_this_iter = true;
		update_q = false;
	}

	if(!drawn_this_iter && update_p){
		pg->setBargraphVal(2,p_val);
		drawn_this_iter = true;
		update_p = false;
	}

	if(!drawn_this_iter && update_ps){
		pg->setBargraphVal(3,ps_val);
		drawn_this_iter = true;
		update_ps = false;
	}

	if (!drawn_this_iter && (((loopCount / 5) + 3) % 4) == 0 && ((loopCount % 5) == 0))
	{
		drawn_this_iter = true;
		Page::loop(loopCount, pg);
	}
}
