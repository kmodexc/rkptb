#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <Wire.h>

#include "pindefs.h"
#include "Graphics.h"

#include "helpers.h"

#define WR_BUF_LEN 100
#define SEND_BUF_LEN 250


class Display : public Graphics{
	
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
	

	void sendStr(char* str,size_t len);
	
	/************************************************************************/
	// sends a message len at display                                                                     */
	/************************************************************************/
	void send(const char *str,size_t len);
	
	/************************************************************************/
	// send a message with specified control argument at display                                                                     */
	/************************************************************************/
	void send(const char *str,size_t len,uint8_t control);
	
	/************************************************************************/
	// requests the send-buffer from display. This method is not called in loop so 
	/************************************************************************/
	bool requestBuffer(uint8_t *buffer,size_t size);
	
	
	void command(const char* cmd);
	
	
	void command(const char* cmd,bool extra_null);
	
	
	bool text(int x,int y,char* txt);
	
	
	bool text(DisplayText* txt);
	
	
	bool text(DisplayText* txt,uint8_t max_redraw_char);
	
	
	void drawChar(int x,int y,char c);
	
	
	void dispNumber(DisplayFloat* num);
	

	void clearRect(size_t x0,size_t y0,size_t x1,size_t y1);
	
	
	bool setFontColor(uint8_t vf,uint8_t hf);
	
	
	protected:
	
	/************************************************************************/
	/* internal method for sending a buffer                                                                     */
	/************************************************************************/
	bool intern_send_buf(uint8_t* buf,uint8_t len,uint8_t control);
	
	/************************************************************************/
	/* temporary buffer for any byte operation needed                                                                     */
	/************************************************************************/
	char tmp_buf[WR_BUF_LEN];
	
	private:
	
	/************************************************************************/
	/* send buffer only for send methods                                                                     */
	/************************************************************************/
	uint8_t send_buf[SEND_BUF_LEN];
	
	/************************************************************************/
	/* send buffer next free index                                                                     */
	/************************************************************************/
	uint8_t* send_buf_next;
	
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