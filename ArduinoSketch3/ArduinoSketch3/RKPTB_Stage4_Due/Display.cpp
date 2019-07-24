#ifndef _DISPLAY_CPP_
#define _DISPLAY_CPP_

#include "Application.h"

void Display::initialize() {
  Wire.begin();
  delay(100);
  Serial.begin(9600);
}

void Display::loop(unsigned long loopCount) {

}

void Display::clearStr(char* str, size_t len) {
  if (str == 0 || len <= 0 || len > 100) {
    return;
  }
  char* it_end = str + len;
  for (char* it = str; it != it_end; it++) {
    *it = ' ';
  }
  str[len - 1] = 0;
}

void Display::sendStr(char* str, size_t len) {
  str[len - 2] = LF;
  str[len - 1] = CR;
  send(str, len);
}

void Display::send(char* str, size_t len) {
  send(str, len, DC1);
}

void Display::send(char* str, size_t len, uint8_t control) {
  if (len <= 0) return;
  if (Serial) Serial.println(str);
  uint8_t fb = NAK;
  do {
    uint8_t bcc = control;
    Wire.beginTransmission(DISPLAY_WRITE_ADDR);
    Wire.write(control); //DC1
    Wire.write(len);  //DataLength
    bcc += len;
    for (char *it = str; it != str + len; it++) {
      Wire.write((uint8_t)(*it));
      bcc += (uint8_t)(*it);
    }
    Wire.write(bcc);
    Wire.endTransmission();

    if (Wire.requestFrom(DISPLAY_READ_ADDR, (uint8_t)1) > 0) {
      fb = Wire.read();
    }
    if (fb == NAK) {
      delay(100);
    }
    if (Serial) {
      Serial.print("fb = ");
      Serial.println(fb);
    }

  } while (fb == NAK);

  clearStr(str, len);
}

void Display::printFloat(char* str, int32_t length, int32_t iNum)
{
  if (iNum < 0) iNum = 0;
  if (5 > length) return;
  str[4] = (iNum % 10) + 48;
  iNum /= 10;
  str[3] = (iNum % 10) + 48;
  iNum /= 10;
  str[2] = '.';
  str[1] = (iNum % 10) + 48;
  iNum /= 10;
  str[0] = (iNum % 10) + 48;
}

void Display::printInt(char* str, int32_t length, int32_t iNum) {
  if (iNum < 0) iNum = 0;
  if (4 > length) return;
  str[3] = (iNum % 10) + 48;
  iNum /= 10;
  str[2] = (iNum % 10) + 48;
  iNum /= 10;
  str[1] = (iNum % 10) + 48;
  iNum /= 10;
  str[0] = (iNum % 10) + 48;
}

size_t Display::dynIntToStr(char* str, size_t lenMax, int32_t iNum) {
  if (lenMax <= 0) return 0;
  int tmp = iNum;
  int len = 1;
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

void Display::command(char* cmd) {
  size_t cnt = 0;
  char* it = cmd;
  char* wr_it = wr_buf;
  while (*(it) != 0) {
    *(wr_it++) = *(it++);
  }
  send(wr_buf, (wr_it - wr_buf) + 1);
}


void Display::text(int x, int y, char* txt) {
  //clearRect(x,y,x+250,y+25);

  char* writ = wr_buf;
  *(writ++) = '#';
  *(writ++) = 'Z';
  *(writ++) = 'L';
  writ += dynIntToStr(writ, 4, x);
  *(writ++) = ',';
  writ += dynIntToStr(writ, 4, y);
  *(writ++) = ',';
  for (char* it = txt; *it != 0 && writ < (wr_buf + WR_BUF_LEN - 3 - 69); it++) {
    *(writ++) = *it;
  }
  *(writ++) = 0;
  send(wr_buf, writ - wr_buf);
}

void Display::text(DisplayText* txt) {
  if (txt->update == false) return;

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
  } else {
    for (uint8_t cnt = 0; cnt < DisplayText::STRLEN && txt->old_str[cnt] && txt->new_str[cnt] ; cnt++) {
      if (txt->old_str[cnt] != txt->new_str[cnt]) {
        if (txt->drawn) {
          setFontColor(0, 0);
          drawChar(txt->x + (cnt * dx), txt->y, txt->old_str[cnt]);
        }
        setFontColor(8, 0);
        drawChar(txt->x + (cnt * dx), txt->y, txt->new_str[cnt]);
      }
    }
    for (uint8_t cnt = len_new_str; cnt < len_old_str && txt->drawn ; cnt++) {
      setFontColor(0, 0);
      drawChar(txt->x + (cnt * dx), txt->y, txt->old_str[cnt]);
    }
    for (uint8_t cnt = len_old_str; cnt < len_new_str; cnt++) {
      setFontColor(8, 0);
      drawChar(txt->x + (cnt * dx), txt->y, txt->new_str[cnt]);
    }
  }

  if (!txt->drawCharwise) {
    setFontColor(8, 0);
    text(txt->x, txt->y, txt->new_str);
  }
  cpystr(txt->old_str, txt->new_str);
  txt->drawn = true;
  txt->update = false;
}

void Display::drawChar(int x, int y, char c) {
  char* writ = wr_buf;
  *(writ++) = '#';
  *(writ++) = 'Z';
  *(writ++) = 'L';
  writ += dynIntToStr(writ, 4, x);
  *(writ++) = ',';
  writ += dynIntToStr(writ, 4, y);
  *(writ++) = ',';
  *(writ++) = c;
  *(writ++) = 0;
  send(wr_buf, writ - wr_buf);
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

void Display::cpystr(char* dest, char* src) {
  for (size_t cnt = 0; src[cnt] != 0; cnt++) {
    dest[cnt] = src[cnt];
  }
}

void Display::cpystr(char* dest, const char* src) {
  cpystr(dest, (char*)src);
}

void Display::clearRect(size_t x0, size_t y0, size_t x1, size_t y1) {
  char* writ = wr_buf;
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
  send(wr_buf, writ - wr_buf);
}

void Display::setFontColor(int vf, int hf) {
  char* writ = wr_buf;
  *(writ++) = '#';
  *(writ++) = 'F';
  *(writ++) = 'Z';
  writ += dynIntToStr(writ, 1, vf);
  *(writ++) = ',';
  writ += dynIntToStr(writ, 1, hf);
  *(writ++) = ',';
  send(wr_buf, writ - wr_buf);
}


#endif