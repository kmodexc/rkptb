#include "AboutPage.h"

void AboutPage::repaint(Graphics *pg)
{
    Page::repaint(pg);

    pg->createButton(0, 0, 5, "Menu");
    pg->flush();

    DisplayText name(320, 210, "RKP-TestBox");
    pg->text(&name);
    pg->flush();

    DisplayText version(320, 250, "SW-Ver: 1.4.0-d");
    pg->text(&version);
    pg->flush();
}