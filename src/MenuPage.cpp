#include "MenuPage.h"

void MenuPage::initialize(Graphics *pg)
{
    Page::initialize(pg);
}
void MenuPage::repaint(Graphics *pg)
{
    // delete display
    FCMD(pg,"#DL");
    FCMD(pg,"#FE0,0,0,0,0,0,"); // make colorless buttons 
    FCMD(pg,"#AT0,0,800,480,0,0,\x0d"); // make last buttons unreachable
    
    pg->createButton(0,0,30,"Back");
    pg->createButton(100,0,31,"Prec");
    pg->createButton(200,0,32,"CurPg");
}
void MenuPage::loop(uint64_t loopCount, Graphics *disp)
{
    Page::loop(loopCount, disp);
}