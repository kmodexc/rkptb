#pragma once

#include "helpers.h"
#include "pindefs.h"
#include <stddef.h>
#include <stdint.h>

namespace rkp
{
namespace commands
{
namespace ascii
{
size_t create_button_reseting(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t set_code, uint8_t ret_code, const char *name);
size_t set_font_color(uint8_t *dest, size_t dest_size, uint8_t vf, uint8_t bf);
size_t draw_text(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, const char *str);
size_t request_send_buffer(uint8_t *dest, size_t dest_size);
size_t clear_rectengular_space(uint8_t *dest, size_t dest_size, size_t x0, size_t y0, size_t x1, size_t y1);
size_t set_button_colors(uint8_t *dest, size_t dest_size, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t s1, uint8_t s2, uint8_t s3);
size_t clear_display(uint8_t *dest, size_t dest_size);
size_t clear_touch_area(uint8_t *dest, size_t dest_size);
size_t create_bargraph(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t aw, uint8_t ew, uint8_t typ);
size_t set_bargraph_font(uint8_t *dest, size_t dest_size, uint8_t font);
size_t set_bargraph_skale(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y2, const char *format);
size_t enable_touch_set_bar(uint8_t *dest, size_t dest_size, uint8_t code);
size_t set_bar_val(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t val);
size_t disable_terminal(uint8_t *dest, size_t dest_size);
size_t set_font_type(uint8_t *dest, size_t dest_size, uint8_t font);
size_t set_instrument_val_sendmode(uint8_t *dest, size_t dest_size, uint8_t send_mode);
size_t create_editbox(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t maxChars, size_t x1, size_t y1, size_t x2, size_t y2, const char *defstr);
size_t activate_editbox(uint8_t *dest, size_t dest_size, uint8_t code);
} // namespace ascii
namespace bin
{
size_t create_button_reseting(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t set_code, uint8_t ret_code, const char *name);
size_t set_font_color(uint8_t *dest, size_t dest_size, uint8_t vf, uint8_t bf);
size_t draw_text(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, const char *str);
size_t request_send_buffer(uint8_t *dest, size_t dest_size);
size_t clear_rectengular_space(uint8_t *dest, size_t dest_size, size_t x0, size_t y0, size_t x1, size_t y1);
size_t set_button_colors(uint8_t *dest, size_t dest_size, uint8_t n1, uint8_t n2, uint8_t n3, uint8_t s1, uint8_t s2, uint8_t s3);
size_t clear_display(uint8_t *dest, size_t dest_size);
size_t clear_touch_area(uint8_t *dest, size_t dest_size);
size_t create_bargraph(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t aw, uint8_t ew, uint8_t typ);
size_t set_bargraph_font(uint8_t *dest, size_t dest_size, uint8_t font);
size_t set_bargraph_skale(uint8_t *dest, size_t dest_size, uint8_t code, size_t x1, size_t y2, const char *format);
size_t enable_touch_set_bar(uint8_t *dest, size_t dest_size, uint8_t code);
size_t set_bar_val(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t val);
size_t disable_terminal(uint8_t *dest, size_t dest_size);
size_t set_font_type(uint8_t *dest, size_t dest_size, uint8_t font);
size_t set_instrument_val_sendmode(uint8_t *dest, size_t dest_size, uint8_t send_mode);
size_t create_editbox(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t maxChars, size_t x1, size_t y1, size_t x2, size_t y2, const char *defstr);
size_t activate_editbox(uint8_t *dest, size_t dest_size, uint8_t code);
size_t create_keyboard(uint8_t *dest, size_t dest_size, uint8_t code, const char *codestr);
size_t position_keyboard(uint8_t *dest, size_t dest_size, size_t x1, size_t y1, size_t x2, size_t y2, uint8_t gap);
size_t activate_keyboard(uint8_t *dest, size_t dest_size, uint8_t code, uint8_t editbox);
size_t set_keyboard_special_key_name(uint8_t *dest, size_t len, uint8_t code, const char *name);
size_t set_keyboard_special_key_colors(uint8_t *dest, size_t len, uint8_t n1, uint8_t n2,uint8_t n3,uint8_t s1,uint8_t s2,uint8_t s3);
size_t set_keyboard_borders(uint8_t *dest, size_t len, uint8_t n, uint8_t s);
} // namespace bin
} // namespace commands
} // namespace rkp