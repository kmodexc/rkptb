#include "AnalogPage.h"

void AnalogPage::initialize(Graphics *pg)
{
	Page::initialize(pg);

    dig_bef_com = 1;

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
}

void AnalogPage::repaint(Graphics *pg)
{
	pg->createButton(0, 0, 30, "Back");
	
	// measurement mode switch buttons

	pg->setButtonColor(BCInvisible);
	pg->createButton(420, 100, 460, 120, 1, " ");
	pg->createButton(420, 150, 460, 170, 2, " ");
	pg->createButton(620, 100, 660, 120, 3, " ");
	pg->createButton(620, 150, 660, 170, 4, " ");

	// reset str
	rkp::clearStr(dt_q.old_str, DisplayText::STRLEN);
	rkp::clearStr(dt_p.old_str, DisplayText::STRLEN);
	rkp::clearStr(dt_ps.old_str, DisplayText::STRLEN);
}

void AnalogPage::set_q_set(_float val, Unit un)
{
	val.print(dt_q.new_str + 10, dig_bef_com);
	rkp::unit_print(dt_q.new_str + 16, un);
	dt_q.update = true;
}

void AnalogPage::set_q_is(_float val, Unit un)
{
	val.print(dt_q.new_str + 20, dig_bef_com);
	rkp::unit_print(dt_q.new_str + 26, un);
	dt_q.update = true;
}

void AnalogPage::set_p_set(_float val, Unit un)
{
	val.print(dt_p.new_str + 10, dig_bef_com);
	rkp::unit_print(dt_p.new_str + 16, un);
	dt_p.update = true;
}

void AnalogPage::set_p_is(_float val, Unit un)
{
	val.print(dt_p.new_str + 20, dig_bef_com);
	rkp::unit_print(dt_p.new_str + 26, un);
	dt_p.update = true;
}

void AnalogPage::set_ps_pre_set(_float val, Unit un)
{
	val.print(dt_ps.new_str + 20, dig_bef_com);
	rkp::unit_print(dt_ps.new_str + 26, un);
	dt_ps.update = true;
}

void AnalogPage::set_ps_set(_float val, Unit un)
{
	val.print(dt_ps.new_str + 10, dig_bef_com);
	rkp::unit_print(dt_ps.new_str + 16, un);
	dt_ps.update = true;
}

void AnalogPage::setDigBefCom(uint8_t dbc)
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

uint8_t AnalogPage::getDigBefCom()
{
	return dig_bef_com;
}

void AnalogPage::loop(uint64_t loopCount, Graphics *pg)
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

	if (!drawn_this_iter && (((loopCount / 5) + 3) % 4) == 0 && ((loopCount % 5) == 0))
	{
		drawn_this_iter = true;
		Page::loop(loopCount, pg);
	}
}

