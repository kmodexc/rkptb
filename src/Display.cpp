#ifndef _DISPLAY_CPP_
#define _DISPLAY_CPP_

#include "Application.h"

void Display::initialize() {
	send_buf_next = send_buf;
	Wire.begin();
	delay(100);
	Serial.begin(9600);
}

void Display::loop(unsigned long loopCount) {
	flush();
}

bool Display::flush()
{
	if(intern_send_buf(send_buf,send_buf_next-send_buf,DC1)){
		rkp::clearStr((char*)send_buf,SEND_BUF_LEN);
		send_buf_next = send_buf;
		return true;
	}
	return false;
}

void Display::sendStr(char* str, size_t len) {
	str[len - 2] = LF;
	str[len - 1] = CR;
	send(str, len);
}

void Display::send(const char* str, size_t len) {
	send(str, len, DC1);
}

void Display::send(const char* str, size_t len, uint8_t control) {
	if(control == DC1 && ((send_buf_next - send_buf) + len) < SEND_BUF_LEN){
		for(const char* it = str; it < (str+len) ; it++){
			*(send_buf_next++) = (uint8_t)(*it);
		}
	}
	else{
		intern_send_buf((uint8_t*)str,len,control);
	}
}

bool Display::requestBuffer(uint8_t *buffer,size_t size)
{
	if(size > 0){
		send("S",1,DC2);
		uint8_t* it = buffer;
		if (Wire.requestFrom(DISPLAY_READ_ADDR, (uint8_t)(size+3)) > 0) {
			if(Wire.read() == 17 && Wire.read() != 0){
				while(Wire.available()){
					uint8_t val = Wire.read();
					if(val == 255) break;
					TRACE(val);
					TRACE(' ');
					*(it++) = val;
				}
			}
			while(Wire.available()){
				Wire.read();
			}
		}
		if(it != buffer){
			TRACELN();
			return true;
		}
	}
	return false;
}


size_t Display::dynIntToStr(char* str, size_t lenMax, int32_t iNum) {
	if (lenMax <= 0) return 0;
	int tmp = iNum;
	size_t len = 1;
	if (iNum < 0) {
		len = 2;
		str[0] = '-';
	}
	while ((tmp /= 10) > 0) len++;
	if (len > lenMax) return 0;
	tmp = iNum;
	for (char* it = str + (len - 1); it != (str - 1); it--) {
		*it = (tmp % 10) + 48;
		tmp /= 10;
	}
	return len;
}

void Display::command(const char* cmd) {
	command(cmd,false);
}

void Display::command(const char* cmd,bool extra_null) {
	const char* it = cmd;
	char* wr_it = tmp_buf;
	while (*(it) != 0) {
		*(wr_it++) = *(it++);
	}
	send(tmp_buf, (wr_it - tmp_buf) + (extra_null ? 1 : 0));
}

bool Display::text(int x, int y, char* txt) {
	//clearRect(x,y,x+250,y+25);

	char* writ = tmp_buf;
	*(writ++) = '#';
	*(writ++) = 'Z';
	*(writ++) = 'L';
	writ += dynIntToStr(writ, 4, x);
	*(writ++) = ',';
	writ += dynIntToStr(writ, 4, y);
	*(writ++) = ',';
	for (char* it = txt; *it != 0 && writ < (tmp_buf + WR_BUF_LEN - 3 - 69); it++) {
		*(writ++) = *it;
	}
	*(writ++) = 0;
	send(tmp_buf, writ - tmp_buf);
	
	return true;
}

bool Display::text(DisplayText* txt) {
	return text(txt,2);
}

bool Display::text(DisplayText* txt,uint8_t max_redraw_char)
{
	if (txt->update == false) return false;
	
	if(max_redraw_char == 0) return false;
	
	txt->drawn = true;

	const uint8_t dx = 20;

	uint8_t len_old_str = 0;
	uint8_t len_new_str = 0;

	if (txt->drawCharwise) {
		for (len_old_str = 0; txt->old_str[len_old_str] ; len_old_str++);
		for (len_new_str = 0; txt->new_str[len_new_str] ; len_new_str++);
	}


	if (!txt->drawCharwise) {
		
		if (txt->drawn) {
			setFontColor(0, 0);
			text(txt->x, txt->y, txt->old_str);
		}
		
		setFontColor(8, 0);
		text(txt->x, txt->y, txt->new_str);
		rkp::cpystr(txt->old_str, txt->new_str);
		
		txt->update = false;
		
		return true;
	}
	else
	{ // draw charwise begin
		txt->update = false;
		uint8_t drawn_char_cnt = 0;
		
		// delete part
		if(txt->drawn){
			// delete longer old str
			for (uint8_t cnt = len_new_str; cnt < len_old_str && txt->drawn; cnt++)
			{
				if(txt->old_str[cnt] != ' ')
				{
					if(drawn_char_cnt < max_redraw_char){
						if(setFontColor(0, 0)){
							drawn_char_cnt++;
						}
					}
					if(drawn_char_cnt < max_redraw_char)
					{
						drawChar(txt->x + (cnt * dx), txt->y, txt->old_str[cnt]);
						txt->old_str[cnt] = ' ';
						drawn_char_cnt++;
					}
					else
					{
						txt->update = true;
					}
				}
				
			}
			
			// delete existing parts if something to delete
			for (uint8_t cnt = 0; cnt < DisplayText::STRLEN && txt->old_str[cnt] && txt->new_str[cnt]; cnt++)
			{
				if (txt->old_str[cnt] != txt->new_str[cnt] && txt->old_str[cnt] != ' ')
				{
					// if already in this color mode nothing will be changed
					if(drawn_char_cnt < max_redraw_char){
						if(setFontColor(0, 0)){
							drawn_char_cnt++;
						}
					}
					if(drawn_char_cnt < max_redraw_char)
					{
						drawChar(txt->x + (cnt * dx), txt->y, txt->old_str[cnt]);
						txt->old_str[cnt] = ' ';
						drawn_char_cnt++;
					}
					else{
						txt->update = true;
					}
				}
			}
		} // delete part
		
		
		// draw part
		
		// draw on overlapping parts
		for (uint8_t cnt = 0; cnt < DisplayText::STRLEN && txt->old_str[cnt] && txt->new_str[cnt]; cnt++)
		{
			// only draw deleted parts (marked as space)
			if (txt->old_str[cnt] == ' ' && txt->new_str[cnt] != ' ')
			{
				if(drawn_char_cnt < max_redraw_char){
					if(setFontColor(8, 0)){
						drawn_char_cnt++;
					}
				}
				if(drawn_char_cnt < max_redraw_char)
				{
					drawChar(txt->x + (cnt * dx), txt->y, txt->new_str[cnt]);
					txt->old_str[cnt] = txt->new_str[cnt];
					drawn_char_cnt++;
				}
				else{
					txt->update = true;
				}
			}
		}
		
		
		// draw longer parts new str
		for (uint8_t cnt = len_old_str; cnt < len_new_str; cnt++)
		{
			// only draw deleted parts (marked as space)
			if (txt->old_str[cnt] == ' ' && txt->new_str[cnt] != ' ')
			{
				if(drawn_char_cnt < max_redraw_char){
					if(setFontColor(8, 0)){
						drawn_char_cnt++;
					}
				}
				if(drawn_char_cnt < max_redraw_char)
				{
					drawChar(txt->x + (cnt * dx), txt->y, txt->new_str[cnt]);
					txt->old_str[cnt] = txt->new_str[cnt];
					drawn_char_cnt++;
				}
				else{
					txt->update = true;
				}
			}
		}
		
		// end draw part
		
		// set return values depend on if something was drawn
		if(drawn_char_cnt > 0){
			return true;
		}
		else{
			return false;
		}
	} // end charwise draw
} // end text fuction

void Display::drawChar(int x, int y, char c) {
	char* writ = tmp_buf;
	*(writ++) = '#';
	*(writ++) = 'Z';
	*(writ++) = 'L';
	writ += dynIntToStr(writ, 4, x);
	*(writ++) = ',';
	writ += dynIntToStr(writ, 4, y);
	*(writ++) = ',';
	*(writ++) = c;
	*(writ++) = 0;
	send(tmp_buf, writ - tmp_buf);
}

void Display::dispNumber(DisplayFloat* num)
{
	char str_num[6];
	num->num.print(str_num);
	str_num[5] = 0;

	const uint8_t dx = 10;

	for (uint8_t cnt = 0; cnt < 6; cnt++) {
		if (str_num[cnt] != num->old_str[cnt]) {
			setFontColor(0, 0);
			drawChar(num->x + cnt * dx, num->y, num->old_str[cnt]);
			setFontColor(8, 0);
			drawChar(num->x + cnt * dx, num->y, str_num[cnt]);
			str_num[cnt] = num->old_str[cnt];
		}
	}
}

void Display::clearRect(size_t x0, size_t y0, size_t x1, size_t y1) {
	char* writ = tmp_buf;
	*(writ++) = '#';
	*(writ++) = 'R';
	*(writ++) = 'L';
	writ += dynIntToStr(writ, 4, x0);
	*(writ++) = ',';
	writ += dynIntToStr(writ, 4, y0);
	*(writ++) = ',';
	writ += dynIntToStr(writ, 4, x1);
	*(writ++) = ',';
	writ += dynIntToStr(writ, 4, y1);
	*(writ++) = ',';
	send(tmp_buf, writ - tmp_buf);
}

bool Display::setFontColor(uint8_t vf, uint8_t hf) {
	if(font_color_fg != vf || font_color_bg != hf){
		char* writ = tmp_buf;
		*(writ++) = '#';
		*(writ++) = 'F';
		*(writ++) = 'Z';
		writ += dynIntToStr(writ, 1, vf);
		*(writ++) = ',';
		writ += dynIntToStr(writ, 1, hf);
		*(writ++) = ',';
		send(tmp_buf, writ - tmp_buf);
		font_color_bg = hf;
		font_color_fg = vf;
		return true;
	}
	return false;
}


bool Display::intern_send_buf(uint8_t* buf,uint8_t len,uint8_t control)
{
	if (len <= 0) return false;
	uint8_t fb = NAK;
	do {
		uint8_t bcc = control;
		Wire.beginTransmission(DISPLAY_WRITE_ADDR);
		Wire.write(control); //DC1
		Wire.write(len);  //DataLength
		bcc += len;
		for (uint8_t *it = buf; it != buf + len; it++) {
			Wire.write(*it);
			bcc += *it;
		}
		Wire.write(bcc);
		Wire.endTransmission();
		
		delay(1);

		if (Wire.requestFrom(DISPLAY_READ_ADDR, (uint8_t)1) > 0) {
			fb = Wire.read();
		}
		
		if (fb == NAK) {
			delay(100);
			if (Serial) {
				for(uint8_t* it = buf;it<buf+len;it++){
					Serial.print(*it);
					Serial.print(' ');
				}
				Serial.print("  fb = ");
				Serial.println(fb);
			}
		}
		

	} while (fb != ACK);
	
	return true;
}

#endif
