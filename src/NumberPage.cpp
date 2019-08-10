#include "NumberPage.h"

void NumberPage::initialize(Graphics *pg)
{
    Page::initialize(pg);
}

void NumberPage::repaint(Graphics *pg)
{
    pg->createButton(0, 0, 5, "Menu");
    pg->createEditbox(250, 50, 300, 50, 1);
    pg->createNumpad(250, 150, 1);
}

TouchEvent NumberPage::getTouchEvent()
{
    TouchEvent ev = Page::getTouchEvent();

    return ev;
}

uint8_t NumberPage::getTouchValue()
{
    uint8_t tv = Page::getTouchValue();

    return tv;
}

void NumberPage::loop(uint64_t loopCount, Graphics *pg)
{
    Page::loop(loopCount, pg);
}

void NumberPage::unshow(Graphics *pg)
{
    pg->unshowEditbox(1);
    Page::unshow(pg);
}