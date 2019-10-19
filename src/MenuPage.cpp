#include "MenuPage.h"

void MenuPage::repaint(Graphics *pg)
{
	Page::repaint(pg);

	pg->setButtonColor(BCNormal);
	pg->createButton(0, 0, 30, "MainPage");
	pg->createButton(100, 0, 31, "Tgl|Prec");
	pg->createButton(200, 0, 33, "About");
	//pg->createButton(300,0,34,"Analog");
	//pg->createButton(400,0,32," CurPg");
}