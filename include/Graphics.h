#pragma once

#include <stdint.h>
#include <stddef.h>
#include "_float.h"
#include "DisplayText.h"

#define WR_BUF_LEN 100
#define SEND_BUF_LEN 250

enum ButtonColor
{
	BCGreen,
	BCNormal,
	BCInvisible
};

struct DisplayFloat
{
	_float num;
	char old_str[6];
	int x;
	int y;
};

class Graphics
{
public:
	// flushes the buffer if something in
	virtual bool flush() = 0;

	// requests the send-buffer from display. This method is not called in loop so
	virtual bool requestBuffer(uint8_t *buffer, size_t size) = 0;

	__attribute__((deprecated)) virtual void command(const char *cmd) = 0;

	virtual bool text(DisplayText *txt) = 0;

	virtual bool setFontColor(uint8_t vf, uint8_t hf) = 0;

	virtual void clearScreen() = 0;

	virtual void createButton(size_t x1, size_t y1, uint8_t code, const char *name) = 0;

	virtual void createButton(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code, const char *name) = 0;

	virtual void setButtonColor(ButtonColor c) = 0;

	virtual void createBargraph(size_t x1, size_t y1, uint8_t code, const char *name) = 0;

	virtual void createBargraph(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code, const char *name) = 0;

	virtual void updateBargraphSkale(size_t x1, size_t y1, uint8_t code,const _float &min,const _float &max) = 0;

	virtual void setBargraphVal(uint8_t code, uint8_t val);

	virtual void createEditbox(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code) = 0;

	virtual void createNumpad(size_t xq, size_t y1, uint8_t editbox) = 0;

	virtual void unshowEditbox(uint8_t editbox) = 0;
};