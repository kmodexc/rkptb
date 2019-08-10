#include "MenuPage.h"

void MenuPage::initialize(Graphics *pg)
{
    Page::initialize(pg);
}
void MenuPage::repaint(Graphics *pg)
{    
    pg->setButtonColor(BCNormal);
    pg->createButton(0,0,30,"MainPage");
    pg->createButton(100,0,31,"Tgl|Prec");
    pg->createButton(200,0,33,"About");
    pg->createButton(300,0,34,"Analog");
    //pg->createButton(400,0,32," CurPg");
    //pg->createButton(500,0,35,"NumPg");
}
void MenuPage::loop(uint64_t loopCount, Graphics *disp)
{
    Page::loop(loopCount, disp);
}