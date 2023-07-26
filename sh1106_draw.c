#include "sh1106_draw.h"


#define SH1106_WIDTH 132
#define SH1106_HEIGHT 64


void sh1106_draw_pixel(uint8_t *const buffer,
                       const int16_t x, const int16_t y, const uint8_t color)
{
    if (x < 0 || x >= SH1106_WIDTH)
        return;
    if (y < 0 || y >= SH1106_HEIGHT)
        return;

    int32_t temp1 = (x + (y / 8) * SH1106_WIDTH);
    uint8_t temp2 = 1 << (y % 8);
    if (color) {
        buffer[temp1] |= temp2;
        return;
    }
    buffer[temp1] &= ~temp2;
}


void sh1106_draw_rect(uint8_t *const buffer, const int16_t x0, const int16_t y0, 
                      const uint16_t width, const uint16_t height,
                      const uint8_t color)
{
    const int16_t x1 = (int16_t) (x0 + width);
    const int16_t y1 = (int16_t) (y0 + height);

    /* Draw horizontal lines */
    for (int16_t x = x0; x <= x1; x++) {
        if (x >= SH1106_WIDTH)
            break;
        sh1106_draw_pixel(buffer, x, y0, color);
        sh1106_draw_pixel(buffer, x, y1, color);
    }

    /* Draw vertical lines */
    for (int16_t y = y0; y <= y1; y++) {
        if (y >= SH1106_HEIGHT)
            return;
        sh1106_draw_pixel(buffer, x0, y, color);
        sh1106_draw_pixel(buffer, x1, y, color);
    }
}


void sh1106_draw_rect_filled(uint8_t *const buffer, int16_t x0, int16_t y0,
                             const uint16_t width, const uint16_t height,
                             const uint8_t color)
{
    const int16_t x1 = (int16_t) (x0 + width);
    const int16_t y1 = (int16_t) (y0 + height);

    for (int16_t y = y0; y <= y1; y++) {
        if (y < 0 || y >= SH1106_HEIGHT)
            continue;
        for (int16_t x = x0; x <= x1; x++) {
            if (x < 0 || x >= SH1106_WIDTH)
                continue;
            sh1106_draw_pixel(buffer, x, y, color);
        }
    }
}


void sh1106_draw_line(uint8_t *const buffer,
                      int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                      const uint8_t color)
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
            sh1106_draw_pixel(buffer, x0, y0, color);
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
            sh1106_draw_pixel(buffer, x0, y0, color);
        }
    }
}


void sh1106_draw_circle_filled(uint8_t *const buffer, const uint16_t radius, 
                               const int16_t center_x, const int16_t center_y,
                               const uint8_t color)
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
                sh1106_draw_pixel(buffer, x0, y0, color);
        }
    }
}
