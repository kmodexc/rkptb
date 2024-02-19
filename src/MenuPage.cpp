#include "MenuPage.h"

void MenuPage::repaint(Graphics *pg)
{
	Page::repaint(pg);

	pg->setButtonColor(BCNormal);
	pg->createButton(  0, 0, static_cast<int>(TouchEvent::menu_page_back), "MainPage");
	pg->createButton(100, 0, static_cast<int>(TouchEvent::precision_toggle), "Tgl|Prec");
	pg->createButton(200, 0, static_cast<int>(TouchEvent::go_about_page), "About");
	pg->createButton(300, 0, static_cast<int>(TouchEvent::go_analog_page), "Analog");
	pg->createButton(400, 0, static_cast<int>(TouchEvent::go_current_page), " CurPg");
	pg->createButton(500, 0, static_cast<int>(TouchEvent::pid_enable_toggle), "PID_EN");
}