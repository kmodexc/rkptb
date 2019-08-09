#include "AboutPage.h"

void AboutPage::repaint(Graphics *pg)
{
    pg->clearScreen();
    pg->flush();

    pg->createButton(0,0,40,"Back");
    pg->flush();

    DisplayText name(100,100,"RKP-TestB");
    pg->text(&name);
    pg->flush();

    DisplayText version(100,200,"SW-Ver: 1.2.0");
    pg->text(&version);
    pg->flush();
}