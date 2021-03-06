#ifndef _DISPLAY_CPP_
#define _DISPLAY_CPP_

#include "Application.h"

using namespace rkp::commands::bin;

void Display::initialize()
{
	rkp::clearStr((char *)send_buf, SEND_BUF_LEN);
	send_buf_next = send_buf;
	Wire.begin();
	delay(100);
	Serial.begin(9600);

	// display settings

	send(tmp_buf, disable_terminal(tmp_buf, WR_BUF_LEN));
	flush();
	send(tmp_buf, set_font_type(tmp_buf, WR_BUF_LEN, 6));
	flush();
	send(tmp_buf, set_instrument_val_sendmode(tmp_buf, WR_BUF_LEN, 1));
	flush();

	clearScreen();
}

void Display::loop(unsigned long loopCount)
{
	flush();
}

bool Display::flush()
{
	if (intern_send_buf(send_buf, send_buf_next - send_buf, DC1))
	{
		rkp::clearStr((char *)send_buf, SEND_BUF_LEN);
		send_buf_next = send_buf;
		return true;
	}
	return false;
}

void Display::send(const uint8_t *str, size_t len)
{
	send(str, len, DC1);
}

void Display::send(const uint8_t *str, size_t len, uint8_t control)
{
	if (control == DC1 && ((send_buf_next - send_buf) + len) < SEND_BUF_LEN)
	{
		for (const uint8_t *it = str; it < (str + len); it++)
		{
			*(send_buf_next++) = (*it);
		}
	}
	else
	{
		intern_send_buf(str, len, control);
	}
}

bool Display::requestBuffer(uint8_t *buffer, size_t size)
{
	if (size > 0)
	{
		size_t len = request_send_buffer(tmp_buf, WR_BUF_LEN);
		send(tmp_buf, len, DC2);

		uint8_t *it = buffer;
		if (Wire.requestFrom(DISPLAY_READ_ADDR, (uint8_t)(size + 3)) > 0)
		{
			if (Wire.read() == 17 && Wire.read() != 0)
			{
				while (Wire.available())
				{
					uint8_t val = Wire.read();
					if (val == 255)
						break;
					TRACE(val);
					TRACE(' ');
					*(it++) = val;
				}
			}
			while (Wire.available())
			{
				Wire.read();
			}
		}
		if (it != buffer)
		{
			TRACELN();
			return true;
		}
	}
	return false;
}

void Display::command(const char *cmd)
{
	const char *it = cmd;
	uint8_t *wr_it = tmp_buf;
	while (*(it) != 0)
	{
		*(wr_it++) = (uint8_t) * (it++);
	}
	send(tmp_buf, (wr_it - tmp_buf));
}

bool Display::text(int x, int y, const char *txt)
{
	size_t len = draw_text(tmp_buf, WR_BUF_LEN, x, y, txt);
	send(tmp_buf, len);
	return true;
}

bool Display::text(DisplayText *txt)
{
	return text(txt, 3);
}

bool Display::text(DisplayText *txt, uint8_t max_redraw_char)
{
	if (txt->update == false)
		return false;

	if (max_redraw_char == 0)
		return false;

	const uint8_t dx = 20;

	uint8_t len_old_str = 0;
	uint8_t len_new_str = 0;

	if (txt->drawCharwise)
	{
		for (len_old_str = 0; txt->old_str[len_old_str]; len_old_str++)
			;
		for (len_new_str = 0; txt->new_str[len_new_str]; len_new_str++)
			;
	}

	if (!txt->drawCharwise)
	{

		if (txt->drawn)
		{
			setFontColor(0, 0);
			text(txt->x, txt->y, txt->old_str);
			flush();
		}

		setFontColor(8, 0);
		text(txt->x, txt->y, txt->new_str);
		rkp::cpystr(txt->old_str, txt->new_str);

		txt->update = false;
		txt->drawn = true;

		return true;
	}
	// draw charwise begin
	txt->drawn = true;
	txt->update = false;
	uint8_t drawn_char_cnt = 0;

	// delete part
	if (txt->drawn)
	{
		// delete longer old str
		for (uint8_t cnt = len_new_str; cnt < len_old_str && txt->drawn; cnt++)
		{
			if (txt->old_str[cnt] != ' ')
			{
				if (drawn_char_cnt < max_redraw_char)
				{
					if (setFontColor(0, 0))
					{
						drawn_char_cnt++;
					}
				}
				if (drawn_char_cnt < max_redraw_char)
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
				if (drawn_char_cnt < max_redraw_char)
				{
					if (setFontColor(0, 0))
					{
						drawn_char_cnt++;
					}
				}
				if (drawn_char_cnt < max_redraw_char)
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
	} // delete part

	// draw part

	// draw on overlapping parts
	for (uint8_t cnt = 0; cnt < DisplayText::STRLEN && txt->old_str[cnt] && txt->new_str[cnt]; cnt++)
	{
		// only draw deleted parts (marked as space)
		if (txt->old_str[cnt] == ' ' && txt->new_str[cnt] != ' ')
		{
			if (drawn_char_cnt < max_redraw_char)
			{
				if (setFontColor(8, 0))
				{
					drawn_char_cnt++;
				}
			}
			if (drawn_char_cnt < max_redraw_char)
			{
				drawChar(txt->x + (cnt * dx), txt->y, txt->new_str[cnt]);
				txt->old_str[cnt] = txt->new_str[cnt];
				drawn_char_cnt++;
			}
			else
			{
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
			if (drawn_char_cnt < max_redraw_char)
			{
				if (setFontColor(8, 0))
				{
					drawn_char_cnt++;
				}
			}
			if (drawn_char_cnt < max_redraw_char)
			{
				drawChar(txt->x + (cnt * dx), txt->y, txt->new_str[cnt]);
				txt->old_str[cnt] = txt->new_str[cnt];
				drawn_char_cnt++;
			}
			else
			{
				txt->update = true;
			}
		}
	}

	// end draw part

	// set return values depend on if something was drawn
	if (drawn_char_cnt > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

} // end text fuction

void Display::drawChar(int x, int y, char c)
{
	char mystr[] = " ";
	mystr[0] = c;
	text(x, y, mystr);
}

void Display::dispNumber(DisplayFloat *num)
{
	char str_num[6];
	num->num.print(str_num);
	str_num[5] = 0;

	const uint8_t dx = 10;

	for (uint8_t cnt = 0; cnt < 6; cnt++)
	{
		if (str_num[cnt] != num->old_str[cnt])
		{
			setFontColor(0, 0);
			drawChar(num->x + cnt * dx, num->y, num->old_str[cnt]);
			setFontColor(8, 0);
			drawChar(num->x + cnt * dx, num->y, str_num[cnt]);
			str_num[cnt] = num->old_str[cnt];
		}
	}
}

void Display::clearRect(size_t x0, size_t y0, size_t x1, size_t y1)
{
	size_t len = clear_rectengular_space(tmp_buf, WR_BUF_LEN, x0, y0, x1, y1);
	send(tmp_buf, len);
}

bool Display::setFontColor(uint8_t vf, uint8_t hf)
{
	if (font_color_fg != vf || font_color_bg != hf)
	{
		size_t len = set_font_color(tmp_buf, WR_BUF_LEN, vf, hf);
		send(tmp_buf, len);
		font_color_bg = hf;
		font_color_fg = vf;
		return true;
	}
	return false;
}

void Display::clearScreen()
{
	// delete display
	send(tmp_buf, clear_display(tmp_buf, WR_BUF_LEN));
	flush();
	send(tmp_buf, clear_touch_area(tmp_buf, WR_BUF_LEN));
	flush();
}

void Display::createButton(size_t x1, size_t y1, uint8_t code, const char *name)
{
	createButton(x1 + 10, y1 + 10, 90, 40, code, name);
}

void Display::createButton(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code, const char *name)
{
	size_t len = create_button_reseting(tmp_buf, WR_BUF_LEN, x1, y1, x1 + sx, y1 + sy, 0, code, name);
	send(tmp_buf, len);
	flush();
}

void Display::setButtonColor(ButtonColor c)
{
	switch (c)
	{
	case BCGreen:
		send(tmp_buf, set_button_colors(tmp_buf, WR_BUF_LEN, 8, 1, 4, 8, 1, 7));
		flush();
		break;
	case BCInvisible:
		send(tmp_buf, set_button_colors(tmp_buf, WR_BUF_LEN, 0, 0, 0, 0, 0, 0));
		flush();
		break;
	default:
		send(tmp_buf, set_button_colors(tmp_buf, WR_BUF_LEN, 8, 1, 2, 8, 1, 7));
		flush();
	}
}

void Display::createBargraph(size_t x1, size_t y1, uint8_t code, const char *name)
{
	createBargraph(x1, y1, 650, 50, code, name);
}

void Display::createBargraph(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code, const char *name)
{
	send(tmp_buf, create_bargraph(tmp_buf, WR_BUF_LEN, code, x1, y1, x1 + sx, y1 + sy, 0, 254, 5));
	flush();
	send(tmp_buf, set_bargraph_font(tmp_buf, WR_BUF_LEN, 6));
	flush();
	send(tmp_buf, set_bargraph_skale(tmp_buf, WR_BUF_LEN, code, x1 - 10, y1 + 10, "0=0.0;254=11.0"));
	flush();
	send(tmp_buf, enable_touch_set_bar(tmp_buf, WR_BUF_LEN, code));
	flush();
	send(tmp_buf, draw_text(tmp_buf, WR_BUF_LEN, x1 - 100, y1 + 10, name));
	flush();
}

void Display::updateBargraphSkale(size_t x1, size_t y1,uint8_t code,const _float &min,const _float &max){
	char format_str[] = "0=1234;254=1234 ";
	min.print(format_str+2,1);
	max.print(format_str+11,1);
	send(tmp_buf, set_bargraph_skale(tmp_buf, WR_BUF_LEN, code, x1 - 10, y1 + 10, format_str));
	flush();
}

void Display::setBargraphVal(uint8_t code, uint8_t val)
{
	send(tmp_buf, set_bar_val(tmp_buf, WR_BUF_LEN, code, val));
	flush();
}

void Display::createEditbox(size_t x1, size_t y1, size_t sx, size_t sy, uint8_t code)
{
	send(tmp_buf, create_editbox(tmp_buf, WR_BUF_LEN, code, 0, x1, y1, x1 + sx, y1 + sy, ""));
	flush();
	send(tmp_buf, activate_editbox(tmp_buf, WR_BUF_LEN, code));
	flush();
}

void Display::createNumpad(size_t x1, size_t y1, uint8_t editbox)
{
	send(tmp_buf, create_keyboard(tmp_buf, WR_BUF_LEN, 1, "123|456|789|\\80.\\D"));
	flush();
	send(tmp_buf, position_keyboard(tmp_buf, WR_BUF_LEN, x1,y1,x1+300,y1+300,10));
	flush();
	send(tmp_buf, set_keyboard_special_key_colors(tmp_buf, WR_BUF_LEN, 8,1,2,8,1,7));
	flush();
	send(tmp_buf, set_keyboard_special_key_name(tmp_buf, WR_BUF_LEN, 8," C"));
	flush();
	send(tmp_buf, set_keyboard_special_key_name(tmp_buf, WR_BUF_LEN, 13,"OK"));
	flush();
	send(tmp_buf, set_keyboard_borders(tmp_buf, WR_BUF_LEN, 1,1));
	flush();
	send(tmp_buf, activate_keyboard(tmp_buf, WR_BUF_LEN, 1,editbox));
	flush();
}

void Display::unshowEditbox(uint8_t editbox)
{
	send(tmp_buf, activate_editbox(tmp_buf, WR_BUF_LEN, 0));
	flush();
}

bool Display::intern_send_buf(const uint8_t *buf, uint8_t len, uint8_t control)
{
	if (len <= 0 || buf == nullptr || *buf == 0)
		return false;
	uint8_t fb = NAK;
	do
	{
		uint32_t bcc = control;
		Wire.beginTransmission(DISPLAY_WRITE_ADDR);
		Wire.write(control); //DC1
		Wire.write(len);	 //DataLength
		bcc += len;
		for (const uint8_t *it = buf; it != buf + len; it++)
		{
			Wire.write(*it);
			bcc += *it;
		}
		Wire.write((unsigned char)(bcc % 256));
		Wire.endTransmission();

		delay(1);

		if (Wire.requestFrom(DISPLAY_READ_ADDR, (uint8_t)1) > 0)
		{
			fb = Wire.read();
		}

		if (fb != ACK)
		{
			delay(100);
			if (Serial)
			{
				for (const uint8_t *it = buf; it < buf + len; it++)
				{
					Serial.print(*it);
					Serial.print(' ');
				}
				for (const uint8_t *it = buf; it < buf + len; it++)
				{
					Serial.print((char)*it);
				}
				Serial.print("  fb = ");
				Serial.println(fb);
			}
		}

	} while (fb != ACK);

	return true;
}

#endif
