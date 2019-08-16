#include "DisplayCommands.h"

size_t rkp::commands::ascii::create_button_reseting(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t set_code, uint8_t ret_code, const char *name)
{
    char *it = (char *)dest;
    if (dest == nullptr || dest_size < 30)
        return 0;

    if (name == nullptr)
        return 0;

    char *writ = it;
    *(writ++) = '#';
    *(writ++) = 'A';
    *(writ++) = 'T';
    writ += rkp::dynIntToStr(writ, 4, x1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 4, y1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 4, x2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 4, y2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 2, set_code);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 2, ret_code);
    *(writ++) = ',';
    for (; (*name) != 0;)
    {
        *(writ++) = *(name++);
    }
    *(writ++) = LF;

    return writ - it;
}

size_t rkp::commands::ascii::set_font_color(uint8_t *dest, size_t dest_size, uint8_t vf, uint8_t bf)
{
    if (dest == nullptr || dest_size < 7)
        return 0;

    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'F';
    *(writ++) = 'Z';
    writ += rkp::dynIntToStr(writ, 1, vf);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, bf);
    *(writ++) = ',';

    return writ - (char *)dest;
}

size_t rkp::commands::ascii::draw_text(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, const char *txt)
{
    if (dest == nullptr || txt == nullptr || *txt == 0)
        return 0;

    char *tmp_buf = (char *)dest;

    char *writ = tmp_buf;
    *(writ++) = '#';
    *(writ++) = 'Z';
    *(writ++) = 'L';
    writ += rkp::dynIntToStr(writ, 3, x1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y1);
    *(writ++) = ',';
    for (const char *it = txt; *it != 0 && writ < (tmp_buf + dest_size); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = CR;

    return writ - tmp_buf;
}

size_t rkp::commands::ascii::request_send_buffer(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 1)
        return 0;
    dest[0] = (uint8_t)'S';
    return 1;
}

size_t rkp::commands::ascii::clear_rectengular_space(uint8_t *dest, size_t dest_size, size_t x0, size_t y0, size_t x1, size_t y1)
{
    if (dest == nullptr || dest_size < 19)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'R';
    *(writ++) = 'L';
    writ += rkp::dynIntToStr(writ, 3, x0);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y0);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, x1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y1);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::set_button_colors(uint8_t *dest, size_t dest_size, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t s1, uint8_t s2, uint8_t s3)
{
    if (dest == nullptr || dest_size < 15)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'F';
    *(writ++) = 'E';
    writ += rkp::dynIntToStr(writ, 1, n1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, n2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, n3);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, s1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, s2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, s3);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::clear_display(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 3)
        return 0;
    dest[0] = (uint8_t)'#';
    dest[1] = (uint8_t)'D';
    dest[2] = (uint8_t)'L';
    return 3;
}

size_t rkp::commands::ascii::clear_touch_area(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 7)
        return 0;
    dest[0] = (uint8_t)'#';
    dest[1] = (uint8_t)'A';
    dest[2] = (uint8_t)'L';
    dest[3] = (uint8_t)'0';
    dest[4] = (uint8_t)',';
    dest[5] = (uint8_t)'0';
    dest[6] = (uint8_t)',';
    return 7;
}

size_t rkp::commands::ascii::create_bargraph(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t aw, uint8_t ew, uint8_t typ)
{
    if (dest == nullptr || dest_size < 32)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'B';
    *(writ++) = 'R';
    writ += rkp::dynIntToStr(writ, 2, code);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, x1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, x2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, aw);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, ew);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 1, typ);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::set_bargraph_font(uint8_t *dest, size_t dest_size, uint8_t font)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'B';
    *(writ++) = 'F';
    writ += rkp::dynIntToStr(writ, 1, font);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::set_bargraph_skale(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y1, const char *format)
{
    if (dest == nullptr || dest_size < 15)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'B';
    *(writ++) = 'X';
    writ += rkp::dynIntToStr(writ, 2, code);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, x1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y1);
    *(writ++) = ',';
    for (const char *it = format; *it != 0 && (uint8_t *)writ < (dest + dest_size - 1); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = CR;
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::enable_touch_set_bar(uint8_t *dest, size_t dest_size, uint8_t code)
{
    if (dest == nullptr || dest_size < 6)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'A';
    *(writ++) = 'B';
    writ += rkp::dynIntToStr(writ, 2, code);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::set_bar_val(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t val)
{
    if (dest == nullptr || dest_size < 10)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'B';
    *(writ++) = 'A';
    writ += rkp::dynIntToStr(writ, 2, code);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, val);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::disable_terminal(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 3)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'T';
    *(writ++) = 'A';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::set_font_type(uint8_t *dest, size_t dest_size, uint8_t font)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'Z';
    *(writ++) = 'F';
    writ += rkp::dynIntToStr(writ, 1, font);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::set_instrument_val_sendmode(uint8_t *dest, size_t dest_size, uint8_t send_mode)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'A';
    *(writ++) = 'Q';
    writ += rkp::dynIntToStr(writ, 1, send_mode);
    *(writ++) = ',';
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::create_editbox(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t maxChars, size_t x1, size_t y1, size_t x2, size_t y2, const char *defstr)
{
    if (dest == nullptr || dest_size < 25)
        return 0;
    char *writ = (char *)dest;
    *(writ++) = '#';
    *(writ++) = 'E';
    *(writ++) = 'L';
    writ += rkp::dynIntToStr(writ, 2, code);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 2, maxChars);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, x1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y1);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, x2);
    *(writ++) = ',';
    writ += rkp::dynIntToStr(writ, 3, y2);
    *(writ++) = ',';
    for (const char *it = defstr; it != nullptr && *it != 0 && (uint8_t *)writ < (dest + dest_size - 1); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = CR;
    return ((uint8_t *)writ - dest);
}

size_t rkp::commands::ascii::activate_editbox(uint8_t *dest, size_t dest_size, uint8_t code)
{
    if (dest == nullptr || dest_size < 6)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = '#';
    *(writ++) = 'E';
    *(writ++) = 'A';
    writ += rkp::dynIntToStr((char *)writ, 2, code);
    *(writ++) = ',';
    return (writ - dest);
}

size_t rkp::commands::bin::create_button_reseting(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t set_code, uint8_t ret_code, const char *name)
{
    if (dest == nullptr || dest_size < 14)
        return 0;

    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'A';
    *(writ++) = 'T';
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    *(writ++) = x2 & 0xFF;
    *(writ++) = (x2 >> 8) & 0xFF;
    *(writ++) = y2 & 0xFF;
    *(writ++) = (y2 >> 8) & 0xFF;
    *(writ++) = set_code;
    *(writ++) = ret_code;
    for (; name != nullptr && (*name) != 0 && writ < (dest + dest_size - 1);)
    {
        *(writ++) = *(name++);
    }
    *(writ++) = 0;

    return writ - dest;
}

size_t rkp::commands::bin::set_font_color(uint8_t *dest, size_t dest_size, uint8_t vf, uint8_t bf)
{
    if (dest == nullptr || dest_size < 5)
        return 0;

    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'F';
    *(writ++) = 'Z';
    *(writ++) = vf;
    *(writ++) = bf;

    return writ - dest;
}

size_t rkp::commands::bin::draw_text(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, const char *txt)
{
    if (dest == nullptr || txt == nullptr || *txt == 0)
        return 0;

    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'Z';
    *(writ++) = 'L';
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    for (const char *it = txt; *it != 0 && writ < (dest + dest_size); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = 0;

    return writ - dest;
}

size_t rkp::commands::bin::request_send_buffer(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 1)
        return 0;
    dest[0] = (uint8_t)'S';
    return 1;
}

size_t rkp::commands::bin::clear_rectengular_space(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2)
{
    if (dest == nullptr || dest_size < 11)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'R';
    *(writ++) = 'L';
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    *(writ++) = x2 & 0xFF;
    *(writ++) = (x2 >> 8) & 0xFF;
    *(writ++) = y2 & 0xFF;
    *(writ++) = (y2 >> 8) & 0xFF;
    return writ - dest;
}

size_t rkp::commands::bin::set_button_colors(uint8_t *dest, size_t dest_size, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t s1, uint8_t s2, uint8_t s3)
{
    if (dest == nullptr || dest_size < 9)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'F';
    *(writ++) = 'E';
    *(writ++) = n1;
    *(writ++) = n2;
    *(writ++) = n3;
    *(writ++) = s1;
    *(writ++) = s2;
    *(writ++) = s3;
    return (writ - dest);
}

size_t rkp::commands::bin::clear_display(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 3)
        return 0;
    dest[0] = BIN_ESC;
    dest[1] = (uint8_t)'D';
    dest[2] = (uint8_t)'L';
    return 3;
}

size_t rkp::commands::bin::clear_touch_area(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    dest[0] = BIN_ESC;
    dest[1] = (uint8_t)'A';
    dest[2] = (uint8_t)'L';
    dest[3] = 0;
    dest[4] = 0;
    return 5;
}

size_t rkp::commands::bin::create_bargraph(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t aw, uint8_t ew, uint8_t typ)
{
    if (dest == nullptr || dest_size < 15)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'B';
    *(writ++) = 'R';
    *(writ++) = code;
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    *(writ++) = x2 & 0xFF;
    *(writ++) = (x2 >> 8) & 0xFF;
    *(writ++) = y2 & 0xFF;
    *(writ++) = (y2 >> 8) & 0xFF;
    *(writ++) = aw;
    *(writ++) = ew;
    *(writ++) = typ;
    return (writ - dest);
}

size_t rkp::commands::bin::set_bargraph_font(uint8_t *dest, size_t dest_size, uint8_t font)
{
    if (dest == nullptr || dest_size < 4)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'B';
    *(writ++) = 'F';
    *(writ++) = font;
    return (writ - dest);
}

size_t rkp::commands::bin::set_bargraph_skale(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y1, const char *format)
{
    if (dest == nullptr || dest_size < 10 || format == nullptr || *format == 0)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'B';
    *(writ++) = 'X';
    *(writ++) = code;
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    for (const char *it = format; *it != 0 && writ < (dest + dest_size - 1); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = 0;
    return (writ - dest);
}

size_t rkp::commands::bin::enable_touch_set_bar(uint8_t *dest, size_t dest_size, uint8_t code)
{
    if (dest == nullptr || dest_size < 4)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'A';
    *(writ++) = 'B';
    *(writ++) = code;
    return (writ - dest);
}

size_t rkp::commands::bin::set_bar_val(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t val)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'B';
    *(writ++) = 'A';
    *(writ++) = code;
    *(writ++) = val;
    return (writ - dest);
}

size_t rkp::commands::bin::disable_terminal(uint8_t *dest, size_t dest_size)
{
    if (dest == nullptr || dest_size < 3)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'T';
    *(writ++) = 'A';
    return (writ - dest);
}

size_t rkp::commands::bin::set_font_type(uint8_t *dest, size_t dest_size, uint8_t font)
{
    if (dest == nullptr || dest_size < 4)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'Z';
    *(writ++) = 'F';
    *(writ++) = font;
    return (writ - dest);
}

size_t rkp::commands::bin::set_instrument_val_sendmode(uint8_t *dest, size_t dest_size, uint8_t send_mode)
{
    if (dest == nullptr || dest_size < 4)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'A';
    *(writ++) = 'Q';
    *(writ++) = send_mode;
    return (writ - dest);
}

size_t rkp::commands::bin::create_editbox(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t maxChars, size_t x1, size_t y1, size_t x2, size_t y2, const char *defstr)
{
    if (dest == nullptr || dest_size < 14)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'E';
    *(writ++) = 'L';
    *(writ++) = code;
    *(writ++) = maxChars;
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    *(writ++) = x2 & 0xFF;
    *(writ++) = (x2 >> 8) & 0xFF;
    *(writ++) = y2 & 0xFF;
    *(writ++) = (y2 >> 8) & 0xFF;
    for (const char *it = defstr; it != nullptr && *it != 0 && (uint8_t *)writ < (dest + dest_size - 1); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = 0;
    return (writ - dest);
}

size_t rkp::commands::bin::activate_editbox(uint8_t *dest, size_t dest_size, uint8_t code)
{
    if (dest == nullptr || dest_size < 4)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'E';
    *(writ++) = 'A';
    *(writ++) = code;
    return (writ - dest);
}

size_t rkp::commands::bin::create_keyboard(uint8_t *dest, size_t dest_size, uint8_t code, const char *codestr)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'K';
    *(writ++) = 'B';
    *(writ++) = code;
    for (const char *it = codestr; it != nullptr && *it != 0 && (uint8_t *)writ < (dest + dest_size - 1); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = 0;
    return (writ - dest);
}

size_t rkp::commands::bin::position_keyboard(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t gap)
{
    if (dest == nullptr || dest_size < 12)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'K';
    *(writ++) = 'P';
    *(writ++) = x1 & 0xFF;
    *(writ++) = (x1 >> 8) & 0xFF;
    *(writ++) = y1 & 0xFF;
    *(writ++) = (y1 >> 8) & 0xFF;
    *(writ++) = x2 & 0xFF;
    *(writ++) = (x2 >> 8) & 0xFF;
    *(writ++) = y2 & 0xFF;
    *(writ++) = (y2 >> 8) & 0xFF;
    *(writ++) = gap;
    return (writ - dest);
}

size_t rkp::commands::bin::activate_keyboard(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t editbox)
{
    if (dest == nullptr || dest_size < 5)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'K';
    *(writ++) = 'S';
    *(writ++) = code;
    *(writ++) = editbox;
    return (writ - dest);
}

size_t rkp::commands::bin::set_keyboard_special_key_name(uint8_t *dest, size_t len, uint8_t code, const char *name){
	if (dest == nullptr || len < 5)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'K';
    *(writ++) = 'L';
    *(writ++) = code;
    for (const char *it = name; it != nullptr && *it != 0 && (uint8_t *)writ < (dest + len - 1); it++)
    {
        *(writ++) = *it;
    }
    *(writ++) = 0;
    return (writ - dest);
}

size_t rkp::commands::bin::set_keyboard_special_key_colors(uint8_t *dest, size_t len, uint8_t n1, uint8_t n2,uint8_t n3,uint8_t s1,uint8_t s2,uint8_t s3){
	if (dest == nullptr || len < 9)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'F';
    *(writ++) = 'S';
    *(writ++) = n1;
	*(writ++) = n2;
	*(writ++) = n3;
	*(writ++) = s1;
	*(writ++) = s2;
	*(writ++) = s3;  
    return (writ - dest);
}

size_t rkp::commands::bin::set_keyboard_borders(uint8_t *dest, size_t len, uint8_t n, uint8_t s)
{
	if (dest == nullptr || len < 5)
        return 0;
    uint8_t *writ = dest;
    *(writ++) = BIN_ESC;
    *(writ++) = 'K';
    *(writ++) = 'E';
    *(writ++) = n;
	*(writ++) = s;
    return (writ - dest);
}