#include "MenuPage.h"

void MenuPage::initialize(Graphics *pg)
{
}
void MenuPage::repaint(Graphics *pg)
{
    // delete display
    FCMD(pg,"#DL");
    FCMD(pg,"#FE0,0,0,0,0,0,"); // make colorless buttons 
    FCMD(pg,"#AT0,0,800,480,0,0,\x0d"); // make last buttons unreachable
    FCMD(pg,"#FE8,1,2,8,1,7,"); // make colored button
    FCMD(pg,"#AT10,10,100,50,30,0,Back\x0d");
    FCMD(pg,"#AT110,10,200,50,31,0,Prec\x0d");
}
void MenuPage::loop(uint64_t loopCount, Graphics *disp)
{
    Page::loop(loopCount, disp);
}