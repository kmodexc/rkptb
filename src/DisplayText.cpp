#include "DisplayText.h"

using namespace rkp;

DisplayText::DisplayText()
{
    clearStr(new_str,STRLEN);
    clearStr(old_str,STRLEN);
    drawn = false;
    x = 10;
    y = 10;
    update = false;
    drawCharwise = false;
}

DisplayText::DisplayText(int mx, int my, const char *str)
    : DisplayText()
{
    this->x = mx;
    this->y = my;
    cpystr(new_str,str);
    new_str[strlen(str)] = 0;
    old_str[strlen(str)] = 0;
    update = true;
}