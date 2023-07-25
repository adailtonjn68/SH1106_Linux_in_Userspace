#ifndef SH1106_DRIVER_H_
#define SH1106_DRIVER_H_


#include <stdint.h>
#include <unistd.h>


#define SH1106_WIDTH	132
#define SH1106_HEIGHT	64
#define SH1106_SIZE		(SH1106_WIDTH * SH1106_HEIGHT / 8)

#define SH1106_RIGHT_HORIZONTAL_SCROLL              0x26
#define SH1106_LEFT_HORIZONTAL_SCROLL               0x27
#define SH1106_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SH1106_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
#define SH1106_DEACTIVATE_SCROLL                    0x2E // Stop scroll
#define SH1106_ACTIVATE_SCROLL                      0x2F // Start scroll
#define SH1106_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range


ssize_t sh1106_write_command(const int fd, const uint8_t cmd);
ssize_t sh1106_write_datum(const int fd, const uint8_t datum);
ssize_t sh1106_write_buffer(const int fd, const uint8_t *const data,
                            const uint16_t n_bytes);
void sh1106_init(const int fd, uint8_t *const buffer);
void sh1106_fill(uint8_t *const buffer, const uint8_t color);
void sh1106_update_screen(const int fd, const uint8_t *const buffer);
void sh1106_turnoff(const int fd);


#endif /* SH1106_DRIVER_H_ */  
