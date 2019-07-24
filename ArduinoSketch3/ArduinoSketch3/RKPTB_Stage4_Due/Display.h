#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <Wire.h>

#include "pindefs.h"

#define WR_BUF_LEN 100

struct DisplayText{
	static const size_t STRLEN = 30;
	char new_str[STRLEN];
	char old_str[STRLEN];
	bool drawn;
	int x;
	int y;
	bool update;
	bool drawCharwise;
};

struct DisplayFloat{
	_float num;
	char old_str[6];
	int x;
	int y;
};

class Display{
	char wr_buf[WR_BUF_LEN];
	public:
	void initialize();
	void loop(unsigned long cnt);
	void clearStr(char* str,size_t len);
	void sendStr(char* str,size_t len);
	void send(char *str,size_t len);
	void send(char *str,size_t len,uint8_t control);
	void printFloat(char* str, int32_t length, int32_t iNum);
	void printInt(char* str, int32_t length, int32_t iNum);
	size_t dynIntToStr(char* str,size_t maxLen,int32_t iNum);
	void command(char* cmd);
	void text(int x,int y,char* txt);
	void text(DisplayText* txt);
	void drawChar(int x,int y,char c);
	void dispNumber(DisplayFloat* num);
	void cpystr(char* dest, char* src);
	void cpystr(char* dest, const char* src);
	void clearRect(size_t x0,size_t y0,size_t x1,size_t y1);
	void setFontColor(int vf,int hf);
};

#endif
