#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <Wire.h>

#include "pindefs.h"

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

class Display{
	
	public:
	
	/************************************************************************/
	/* initializes display class components                                                                     */
	/************************************************************************/
	void initialize();
	
	/************************************************************************/
	/* loop cycle called function where the messages will be send as one                                                                     */
	/************************************************************************/
	void loop(unsigned long cnt);
	
	/************************************************************************/
	/* flushes the buffer if something in                                                                     */
	/************************************************************************/
	bool flush();
	
	void clearStr(char* str,size_t len);
	
	
	void sendStr(char* str,size_t len);
	
	/************************************************************************/
	/* sends a message len at display                                                                     */
	/************************************************************************/
	void send(char *str,size_t len);
	
	/************************************************************************/
	/* send a message with specified control argument at display                                                                     */
	/************************************************************************/
	void send(char *str,size_t len,uint8_t control);
	
	/************************************************************************/
	/* requests the send-buffer from display. This method is not called in loop so 
	/* use this carefully                                                 */
	/************************************************************************/
	bool requestBuffer(uint8_t *buffer,size_t size);
	
	
	void printFloat(char* str, int32_t length, int32_t iNum);
	
	
	void printInt(char* str, int32_t length, int32_t iNum);
	
	
	size_t dynIntToStr(char* str,size_t maxLen,int32_t iNum);
	
	
	void command(char* cmd);
	
	
	void command(char* cmd,bool extra_null);
	
	
	bool text(int x,int y,char* txt);
	
	
	bool text(DisplayText* txt);
	
	
	bool text(DisplayText* txt,uint8_t max_redraw_char);
	
	
	void drawChar(int x,int y,char c);
	
	
	void dispNumber(DisplayFloat* num);
	
	
	void cpystr(char* dest, char* src);
	
	
	void cpystr(char* dest, const char* src);
	
	
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
