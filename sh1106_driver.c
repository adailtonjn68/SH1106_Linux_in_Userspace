#include "sh1106_driver.h"
#include <unistd.h>
#include <string.h>


ssize_t sh1106_write_command(const int fd, const uint8_t cmd)
{
    uint8_t buffer[2];

    buffer[0] = 0x00;
    buffer[1] = cmd;

    return write(fd, buffer, sizeof(buffer));
}


ssize_t sh1106_write_datum(const int fd, const uint8_t datum)
{
    uint8_t buffer[2];

    buffer[0] = 0x40;
    buffer[1] = datum;

    return write(fd, buffer, sizeof(buffer));
}


ssize_t sh1106_write_buffer(const int fd, const uint8_t *const data,
                            const uint16_t n_bytes) 
{
    uint8_t buffer[n_bytes + 1];
    buffer[0] = 0x40;
    memcpy(&buffer[1], data, n_bytes);
    return write(fd, buffer, sizeof(buffer));
}


void sh1106_init(const int fd, uint8_t *const buffer)
{   
    sh1106_write_command(fd, 0xAE); //display off
	sh1106_write_command(fd, 0x20); //Set Memory Addressing Mode
	sh1106_write_command(fd, 0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	sh1106_write_command(fd, 0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	sh1106_write_command(fd, 0xC8); //Set COM Output Scan Direction
	sh1106_write_command(fd, 0x00); //---set low column address
	sh1106_write_command(fd, 0x10); //---set high column address
	sh1106_write_command(fd, 0x40); //--set start line address
	sh1106_write_command(fd, 0x81); //--set contrast control register
	sh1106_write_command(fd, 0xFF);
	sh1106_write_command(fd, 0xA1); //--set segment re-map 0 to 127
	sh1106_write_command(fd, 0xA6); //--set normal display
	sh1106_write_command(fd, 0xA8); //--set multiplex ratio(1 to 64)
	sh1106_write_command(fd, 0x3F); //
	sh1106_write_command(fd, 0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	sh1106_write_command(fd, 0xD3); //-set display offset
	sh1106_write_command(fd, 0x00); //-not offset
	sh1106_write_command(fd, 0xD5); //--set display clock divide ratio/oscillator frequency
	sh1106_write_command(fd, 0xF0); //--set divide ratio
	sh1106_write_command(fd, 0xD9); //--set pre-charge period
	sh1106_write_command(fd, 0x22); //
	sh1106_write_command(fd, 0xDA); //--set com pins hardware configuration
	sh1106_write_command(fd, 0x12);
	sh1106_write_command(fd, 0xDB); //--set vcomh
	sh1106_write_command(fd, 0x20); //0x20,0.77xVcc
	sh1106_write_command(fd, 0x8D); //--set DC-DC enable
	sh1106_write_command(fd, 0x14); //
	sh1106_write_command(fd, 0xAF); //--turn on SH1106 panel

    sh1106_write_command(fd, SH1106_DEACTIVATE_SCROLL);

    sh1106_fill(buffer, 0x00);

    sh1106_update_screen(fd, buffer);
}


void sh1106_fill(uint8_t *const buffer, const uint8_t color)
{
    memset(buffer, (color == 0x00) ? 0x00 : 0xFF, SH1106_SIZE);
}


void sh1106_update_screen(const int fd, const uint8_t *const buffer)
{
    for (uint8_t m = 0; m < 8; m++) {
        sh1106_write_command(fd, 0xB0 + m);
        sh1106_write_command(fd, 0x00);
        sh1106_write_command(fd, 0x10); 

        sh1106_write_buffer(fd, &buffer[SH1106_WIDTH * m], SH1106_WIDTH);
    }
}


void sh1106_turnoff(const int fd)
{
    sh1106_write_command(fd, 0x8D);
	sh1106_write_command(fd, 0x10);
	sh1106_write_command(fd, 0xAE);
}
