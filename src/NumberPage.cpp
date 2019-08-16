#include "NumberPage.h"

void NumberPage::initialize(Graphics *pg)
{
    mVal = 0.0;
    Page::initialize(pg);
}

void NumberPage::repaint(Graphics *pg)
{
    Page::repaint(pg);
    //pg->createButton(0, 0, 5, "Menu");
    pg->createEditbox(250, 50, 300, 50, 1);
    pg->createNumpad(250, 150, 1);
}

TouchEvent NumberPage::getTouchEvent()
{
    TouchEvent ev = Page::getTouchEvent();
    double exp = 1.0;
    uint8_t *ptr_point = Page::getTouchData();
    switch (ev)
    {
    case nothing:
        break;
    case editbox_data_avail:
        mVal = 0.0;
        for (uint8_t *it = Page::getTouchData(); it != nullptr && it < Page::getTouchData() + TOUCH_EVENT_DATA_SIZE && *it != '.' && *it != 0; it++)
        {
            ptr_point++;
        }
        for (uint8_t *it = ptr_point - 1; it != nullptr && it >= Page::getTouchData() && *it != 0 && *it <= '9' && *it >= '0'; it--)
        {
            mVal += (*it - 48) * exp;
            exp *= 10;
        }
        exp = 0.1f;
        for (uint8_t *it = ptr_point + 1; it != nullptr && it >= Page::getTouchData() && *it != 0 && *it <= '9' && *it >= '0'; it--)
        {
            mVal += ((*it - 48) * exp);
            exp /= 10;
        }
        ev = number_page_enter;
        break;
    default:
        TRACELN("unknown event detected (numpage)");
        break;
    }
    return ev;
}

uint8_t *NumberPage::getTouchData()
{
    uint8_t *td = Page::getTouchData();

    return td;
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

double NumberPage::getValue(){
    return mVal;
}