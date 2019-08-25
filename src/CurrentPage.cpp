#include "CurrentPage.h"

using namespace rkp;
using namespace rkp::r10k;

void CurrentPage::initialize(Graphics *pg)
{
	Page::initialize(pg);

	dt_1.drawCharwise = true;
	dt_1.x = 100;
	dt_1.y = 100;
	clearStr(dt_1.new_str, DisplayText::STRLEN);
	clearStr(dt_1.old_str, DisplayText::STRLEN);
	cpystr(dt_1.new_str, " ");

	dt_2.drawCharwise = true;
	dt_2.x = 100;
	dt_2.y = 150;
	clearStr(dt_2.new_str, DisplayText::STRLEN);
	clearStr(dt_2.old_str, DisplayText::STRLEN);
	cpystr(dt_2.new_str, " ");

	dt_3.drawCharwise = true;
	dt_3.x = 100;
	dt_3.y = 200;
	clearStr(dt_3.new_str, DisplayText::STRLEN);
	clearStr(dt_3.old_str, DisplayText::STRLEN);
	cpystr(dt_3.new_str, " ");
}

void CurrentPage::repaint(Graphics *pg)
{
	Page::repaint(pg);

	pg->createButton(0,0,5,"Menu");

	clearStr(dt_1.old_str, DisplayText::STRLEN);
	clearStr(dt_2.old_str, DisplayText::STRLEN);
	clearStr(dt_3.old_str, DisplayText::STRLEN);
	clearStr(dt_1.new_str, DisplayText::STRLEN);
	clearStr(dt_2.new_str, DisplayText::STRLEN);
	clearStr(dt_3.new_str, DisplayText::STRLEN);
}

void CurrentPage::set_u_adc_raw(uint32_t val)
{
	u_adc = val;
	printInt(dt_1.new_str, 4, val);
	u_adc_direct(val).value.print(dt_1.new_str+10,2);
	set_u_double_rounded(val).value.print(dt_1.new_str+20,2);
	dt_1.update = true;
	updateCurrent();
}

void CurrentPage::set_upre_adc_raw(uint32_t val)
{
	upre_adc = val;
	printInt(dt_2.new_str, 4, val);
	u_adc_direct(val).value.print(dt_2.new_str+10,2);
	set_u_double_rounded(val).value.print(dt_2.new_str+20,2);
	dt_2.update = true;
	updateCurrent();
}

void CurrentPage::loop(uint64_t loopCount, Graphics *pg)
{
	bool drawn_this_iter = false;

	if (!drawn_this_iter && ((loopCount / 5) % 4) == 0)
	{
		drawn_this_iter = pg->text(&dt_1);
	}

	if (!drawn_this_iter && (((loopCount / 5) + 1) % 4) == 0)
	{
		drawn_this_iter = pg->text(&dt_2);
	}

	if (!drawn_this_iter && (((loopCount / 5) + 2) % 4) == 0)
	{
		drawn_this_iter = pg->text(&dt_3);
	}

	if (!drawn_this_iter && (((loopCount / 5) + 3) % 4) == 0 && ((loopCount % 5) == 0))
	{
		drawn_this_iter = true;
		Page::loop(loopCount, pg);
	}
}

void CurrentPage::updateCurrent()
{
	set_i_direct(upre_adc,u_adc).value.print(dt_3.new_str, 2);
	set_i_double_exact(upre_adc,u_adc).value.print(dt_3.new_str + 10, 2);
	set_i_double_rounded(upre_adc,u_adc).value.print(dt_3.new_str + 20, 2);
	dt_3.update = true;
}