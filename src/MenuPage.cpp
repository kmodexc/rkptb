#include "MenuPage.h"

void MenuPage::initialize(Graphics *pg)
{
    Page::initialize(pg);
}
void MenuPage::repaint(Graphics *pg)
{
    pg->clearScreen();
    
    pg->createButton(0,0,30,"Back");
    pg->createButton(100,0,31,"Prec");
    pg->createButton(200,0,32," CurPg");
    pg->createButton(300,0,33,"About");
    pg->createButton(400,0,34,"Analog");
}
void MenuPage::loop(uint64_t loopCount, Graphics *disp)
{
    Page::loop(loopCount, disp);
}