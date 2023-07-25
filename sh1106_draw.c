#include "sh1106_draw.h"


#define SH1106_WIDTH 132
#define SH1106_HEIGHT 64

void sh1106_draw_rect(uint8_t *const buffer, int16_t x0, int16_t y0, 
                      const uint16_t width, const uint16_t height)
{
    const int16_t x1 = (int16_t) (x0 + width);
    const int16_t y1 = (int16_t) (y0 + height);

    int16_t temp1, temp2, temp3, temp4;

    temp1 = (y0 / 8) * SH1106_WIDTH;
    temp2 = 1 << (y0 % 8);
    temp3 = (y1 / 8) * SH1106_WIDTH;
    temp4 = 1 << (y1 % 8);
    for (int16_t x = x0; x <= x1; x++) {
        if (x < 0 || x >= SH1106_WIDTH)
            continue;
        if (y0 >= 0 && y0 < SH1106_HEIGHT)
            buffer[x + temp1] |= (uint8_t) temp2;
        if (y1 >= 0 && y1 < SH1106_HEIGHT)
            buffer[x + temp3] |= (uint8_t) temp4;
    }

    for (int16_t y = y0; y <= y1; y++) {
        if (y < 0 || y >= SH1106_HEIGHT)
            continue;
        temp1 = (y / 8) * SH1106_WIDTH;
        temp2 = 1 << (y % 8);
        if (x0 >= 0 && x0 < SH1106_WIDTH)
            buffer[x0 + temp1] |= (uint8_t) temp2;
        if (x1 >=0 && x1 < SH1106_WIDTH)
            buffer[x1 + temp1] |= (uint8_t) temp2;
    }
}


void sh1106_draw_rect_filled(uint8_t *const buffer, int16_t x0, int16_t y0,
                             const uint16_t width, const uint16_t height)
{
    const int16_t x1 = (int16_t) (x0 + width);
    const int16_t y1 = (int16_t) (y0 + height);
    int16_t temp1, temp2;

    for (int16_t y = y0; y <= y1; y++) {
        if (y < 0 || y >= SH1106_HEIGHT)
            continue;
        temp1 = (y / 8) * SH1106_WIDTH;
        temp2 = 1 << (y % 8);
        for (int16_t x = x0; x <= x1; x++) {
            if (x < 0 || x >= SH1106_WIDTH)
                continue;
            buffer[x + temp1] |= (uint8_t) temp2;
        }
    }
}


void sh1106_draw_line(uint8_t *const buffer,
                      int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{

    int16_t temp1;
    int16_t dx;
    int16_t dy;
    float m;

    dx = x1 - x0;
    dy = y1 - y0;

    if ((dx *dx) > (dy * dy)) {

        if (x0 > x1) {
            temp1 = x0;
            x0 = x1;
            x1 = temp1;
            temp1 = y0;
            y0 = y1;
            y1 = temp1;
        }
        m = (float) dy / (float) dx;
        for (; x0 <= x1; x0++) {
            y0 = (int16_t) (m * (float) (x0 - x1) + (float) y1);
            if (x0 >= 0 && x0 < SH1106_WIDTH && y0 >=0 && y0 < SH1106_HEIGHT) 
                buffer[x0 + (y0 / 8) * SH1106_WIDTH] |= 1 << (y0 % 8);
                
        }
    } else {
        if (y0 > y1) {
            temp1 = y0;
            y0 = y1;
            y1 = temp1;
            temp1 = x0;
            x0 = x1;
            x1 = temp1;
        }
        m = (float) (dx) / (float) (dy);
        for (; y0 <= y1; y0++) {
            x0 = (int16_t) (m * (float) (y0 - y1) + (float) x1);
            if (x0 >= 0 && x0 < SH1106_WIDTH && y0 >=0 && y0 < SH1106_HEIGHT) 
                buffer[x0 + (y0 / 8) * SH1106_WIDTH] |= 1 << (y0 % 8);

        }
    }
}


void sh1106_draw_circle_filled(uint8_t *const buffer, const uint16_t radius, 
                               const int16_t center_x, const int16_t center_y)
{
    int16_t dx, dy;
    const int16_t x1 = (int16_t) (center_x + radius);
    const int16_t y1 = (int16_t) (center_y + radius);

    const uint32_t r_pow_2 = radius * radius;

    for (int16_t x0 = (int16_t) (center_x - radius); x0 <= x1; x0++) {
        if (x0 < 0) 
            continue;
        if (x0 >= SH1106_WIDTH) 
            continue;
        for (int16_t y0 = (int16_t) (center_y - radius); y0 <= y1; y0++) {
            if (y0 < 0) 
                continue;
            if (y0 >= SH1106_HEIGHT)
                continue;
            dx = x0 - center_x;
            dy = y0 - center_y;
            if ((uint32_t) (dx * dx + dy * dy) < r_pow_2) 
                buffer[x0 + (y0 / 8) * SH1106_WIDTH] |= 1 << (y0 % 8);
        }
    }
}
