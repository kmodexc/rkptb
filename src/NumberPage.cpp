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
    switch (ev)
    {
    case editbox_data_avail:
        // todo here
        for(uint8_t *it = Page::getTouchData();it != nullptr && *it != 0 && it < Page::getTouchData() + TOUCH_EVENT_DATA_SIZE;it++){
            
        }
        return nothing;
        break;
    default:
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