#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <Wire.h>

#include "pindefs.h"
#include "Graphics.h"

#include "helpers.h"

#include "DisplayCommands.h"

#define WR_BUF_LEN 100
#define SEND_BUF_LEN 250

class Display : public Graphics
{

public:
	/************************************************************************/
	// initializes display class components                                                                     */
	/************************************************************************/
	void initialize();

	/************************************************************************/
	// loop cycle called function where the messages will be send as one                                                                     */
	/************************************************************************/
	void loop(unsigned long cnt);

	/************************************************************************/
	// flushes the buffer if something in                                                                     */
	/************************************************************************/
	bool flush();

	/************************************************************************/
	// sends a message len at display                                                                     */
	/************************************************************************/
	void send(const uint8_t *str, size_t len);

	/************************************************************************/
	// send a message with specified control argument at display                                                                     */
	/************************************************************************/
	void send(const uint8_t *str, size_t len, uint8_t control);

	/************************************************************************/
	// requests the send-buffer from display. This method is not called in loop so
	/************************************************************************/
	bool requestBuffer(uint8_t *buffer, size_t size);

	__attribute__((deprecated)) void command(const char *cmd);

	bool text(int x, int y, const char *txt);

	bool text(DisplayText *txt);

	bool text(DisplayText *txt, uint8_t max_redraw_char);

	void drawChar(int x, int y, char c);

	void dispNumber(DisplayFloat *num);

	void clearRect(size_t x0, size_t y0, size_t x1, size_t y1);

	bool setFontColor(uint8_t vf, uint8_t hf);

	void clearScreen();

	void createButton(size_t x1, size_t y2, uint8_t code, const char *name);

	void createButton(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code, const char *name);

	void setButtonColor(ButtonColor c);
	
	void createBargraph(size_t x1, size_t y1, uint8_t code, const char *name);

	void createBargraph(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code, const char *name);

	void setBargraphVal(uint8_t code,uint8_t val);

protected:
	/************************************************************************/
	/* internal method for sending a buffer                                                                     */
	/************************************************************************/
	bool intern_send_buf(const uint8_t *buf, uint8_t len, uint8_t control);

	/************************************************************************/
	/* temporary buffer for any byte operation needed                                                                     */
	/************************************************************************/
	uint8_t tmp_buf[WR_BUF_LEN];

private:
	/************************************************************************/
	/* send buffer only for send methods                                                                     */
	/************************************************************************/
	uint8_t send_buf[SEND_BUF_LEN];

	/************************************************************************/
	/* send buffer next free index                                                                     */
	/************************************************************************/
	uint8_t *send_buf_next;

	/************************************************************************/
	/* foreground color at present at display                                                                     */
	/************************************************************************/
	uint8_t font_color_fg;

	/************************************************************************/
	/* background's color present at display                                                                     */
	/************************************************************************/
	uint8_t font_color_bg;
};

#endif
