#pragma once

#include <stdint.h>
#include <stddef.h>
#include "_float.h"

#define WR_BUF_LEN 100
#define SEND_BUF_LEN 250

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

class Graphics{
    public:
	
	// flushes the buffer if something in
	virtual bool flush() = 0;
	
	// requests the send-buffer from display. This method is not called in loop so 
	virtual bool requestBuffer(uint8_t *buffer,size_t size) = 0;
	
	virtual void command(const char* cmd) = 0;
	
	virtual bool text(DisplayText* txt) = 0;
	
	virtual bool setFontColor(uint8_t vf,uint8_t hf) = 0;
};