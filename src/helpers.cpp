#include "helpers.h"


void rkp::clearStr(char* str, size_t len) {
	if (str == 0 || len <= 0) {
		return;
	}
	char* it_end = str + len;
	for (char* it = str; it != it_end; it++) {
		*it = ' ';
	}
	str[len - 1] = 0;
}



void rkp::printFloat(char* str, int32_t length, int32_t iNum)
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

void rkp::printInt(char* str, int32_t lenMax, int32_t iNum) {
	if (lenMax <= 0) return;
	int32_t tmp = iNum;
	int32_t len = 1;
	if (iNum < 0) {
		len = 2;
		str[0] = '-';
	}
	while ((tmp /= 10) > 0) len++;
	if (len > lenMax) return;
	tmp = iNum;
	for (char* it = str + (lenMax - 1); it != (str - 1); it--) {
		*it = (tmp % 10) + 48;
		tmp /= 10;
	}
}

size_t rkp::dynIntToStr(char* str, size_t lenMax, int32_t iNum) {
	if (lenMax <= 0) return 0;
	int32_t tmp = iNum;
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

void rkp::cpystr(char* dest, char* src) {
	for (size_t cnt = 0; src[cnt] != 0; cnt++) {
		dest[cnt] = src[cnt];
	}
}

void rkp::cpystr(char* dest, const char* src) {
	cpystr(dest, (char*)src);
}

