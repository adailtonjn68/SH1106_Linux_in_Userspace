#ifndef SH1106_DRAW_H_
#define SH1106_DRAW_H_


#include <stdint.h>


void sh1106_draw_rect(uint8_t *const buffer, int16_t x0, int16_t y0, 
                      const uint16_t width, const uint16_t height);
void sh1106_draw_rect_filled(uint8_t *const buffer, int16_t x0, int16_t y0, 
                             const uint16_t width, const uint16_t height);
void sh1106_draw_line(uint8_t *const buffer,
                      int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void sh1106_draw_circle_filled(uint8_t *const buffer, const uint16_t radius, 
                               const int16_t center_x, const int16_t center_y);

#endif /* SH1106_DRAW_H_ */
