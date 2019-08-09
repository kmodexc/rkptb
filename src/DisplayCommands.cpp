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

size_t rkp::commands::ascii::clear_display(uint8_t *dest,size_t dest_size){
    if (dest == nullptr || dest_size < 3)
        return 0;
    dest[0] = (uint8_t)'#';
    dest[1] = (uint8_t)'D';
    dest[2] = (uint8_t)'L';
    return 3;
}