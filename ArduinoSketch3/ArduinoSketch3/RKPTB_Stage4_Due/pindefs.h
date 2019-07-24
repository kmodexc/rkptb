#ifndef _PINDEFS_H_
#define _PINDEFS_H_

const int32_t PIN_ERROR = 33;
const int32_t PIN_RELEASE = 31;
const uint8_t DISPLAY_WRITE_ADDR = 0x6F;
const uint8_t DISPLAY_READ_ADDR = 0x6F;
const uint8_t ACK = 0x06;
const uint8_t NAK = 0x15;
const uint8_t LF = 10;
const uint8_t CR = 13;
const uint8_t DC1 = 0x11;
const uint8_t DC2 = 0x12;

const char STR_P_SET[] = "Psoll";
const char STR_Q_SET[] = "Qsoll";
const char STR_PS_SET[] = "Param";
const char STR_P_IS[] = "Pist";
const char STR_Q_IS[] = "Qist";


#endif
