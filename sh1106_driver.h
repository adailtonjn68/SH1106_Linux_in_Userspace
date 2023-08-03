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
#define SH1106_SET_MULTIPLEX_RATION                 0xA8


enum SH1106_COMMANDS {
    SH1106_SET_PUMP_VOLTAGE_VALUE_64 = 0x30,
    SH1106_SET_PUMP_VOLTAGE_VALUE_74,
    SH1106_SET_PUMP_VOLTAGE_VALUE_80,
    SH1106_SET_PUMP_VOLTAGE_VALUE_90,
    SH1106_SET_DISPLAY_START_LINE = 0x40,
    SH1106_SET_CONTRAST_DATA_REGISTER = 0x81,
    SH1106_SET_SEGMENT_REMAP_NORMAL_DIRECTION = 0xA0,
    SH1106_SET_SEGMENT_REMAP_REVERSE_DIRECTION,
    SH1106_DISPLAY_OFF = 0xAE,
    SH1106_DISPLAY_ON,
    SH1106_SET_PAGE_ADDRESS_0 = 0xB0,
    SH1106_SET_PAGE_ADDRESS_1,
    SH1106_SET_PAGE_ADDRESS_2,
    SH1106_SET_PAGE_ADDRESS_3,
    SH1106_SET_PAGE_ADDRESS_4,
    SH1106_SET_PAGE_ADDRESS_5,
    SH1106_SET_PAGE_ADDRESS_6,
    SH1106_SET_PAGE_ADDRESS_7,
    SH1106_SET_DISPLAY_OFFSET = 0xD3,
    SH1106_SET_VCOM_DESELECT_LEVEL = 0xDB,
    SH1106_NOP = 0xE3,
    SH1106_END = 0xEE,
};


ssize_t sh1106_write_command(const int fd, const uint8_t cmd);
ssize_t sh1106_write_datum(const int fd, const uint8_t datum);
ssize_t sh1106_write_buffer(const int fd, const uint8_t *const data,
                            const uint16_t n_bytes);
void sh1106_init(const int fd, uint8_t *const buffer);
void sh1106_fill(uint8_t *const buffer, const uint8_t color);
void sh1106_update_screen(const int fd, const uint8_t *const buffer);
void sh1106_turnoff(const int fd);


#endif /* SH1106_DRIVER_H_ */  
