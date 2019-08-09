#pragma once

#include <stdint.h>
#include <stddef.h>
#include "helpers.h"
#include "pindefs.h"

namespace rkp
{
namespace commands
{
namespace ascii
{
    size_t create_button_reseting(uint8_t *dest,size_t dest_size,size_t x1,size_t y1,size_t x2, size_t y2,uint8_t set_code,uint8_t ret_code,const char* name);
    size_t set_font_color(uint8_t *dest,size_t dest_size,uint8_t vf,uint8_t bf);
    size_t draw_text(uint8_t *dest,size_t dest_size,size_t x1,size_t y1,const char* str);
    size_t request_send_buffer(uint8_t *dest,size_t dest_size);
    size_t clear_rectengular_space(uint8_t *dest,size_t dest_size,size_t x0, size_t y0, size_t x1, size_t y1);
    size_t set_button_colors(uint8_t *dest,size_t dest_size,uint8_t n1,uint8_t n2,uint8_t n3,uint8_t s1,uint8_t s2,uint8_t s3);
    size_t clear_display(uint8_t *dest,size_t dest_size);
}
} // namespace commands
} // namespace rkp