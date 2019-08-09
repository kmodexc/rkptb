#pragma once

#include <stdint.h>
#include <stddef.h>
#include "helpers.h"

class DisplayText{
public:
    DisplayText();
    DisplayText(int x,int y,const char* str);

    static const size_t STRLEN = 30;
	char new_str[STRLEN];
	char old_str[STRLEN];
	bool drawn;
	int x;
	int y;
	bool update;
	bool drawCharwise;
};