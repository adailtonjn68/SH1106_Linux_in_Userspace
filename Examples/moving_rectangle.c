#include <stdio.h>
#include <fcntl.h>      /* Needed to open I2C file descriptor */ 
#include <unistd.h>     /* Needed to close I2C file descriptor */
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include <time.h>
#include "../sh1106_driver.h"
#include "../sh1106_draw.h"


unsigned char buffer[SH1106_SIZE];

struct rectangle_ {
    struct {
        int x, y;
    } pos, dir;
    uint8_t width, height;
};


void update_rectangle(struct rectangle_ *rect);

int main(void)
{
    srand((unsigned int) time(0));
    
    int status = 0;
    int sh1106_fd;      /* SH1106 file descriptor */
    const char * const dev_name = "/dev/i2c-1";
    const int sh1106_addr = 0x3C;

    sh1106_fd = open(dev_name, O_RDWR);
    if (sh1106_fd < 0) {
        fprintf(stderr, "It was not possible to open %s\n", dev_name);
        return 1;
    }

    printf("%s open\n", dev_name);
    
    status = ioctl(sh1106_fd, I2C_SLAVE, sh1106_addr);
    if (status) {
        fprintf(stderr, "Failed to stablish connection with device\n");
        close(sh1106_fd);
        return status;
    }

    sh1106_init(sh1106_fd, buffer);

    struct rectangle_ rect;
    rect.width = 50;
    rect.height = 20;
    rect.pos.x = rand() % SH1106_WIDTH - rect.width;
    rect.pos.y = rand() % SH1106_HEIGHT - rect.height;
    if (rect.pos.x < 0)
        rect.pos.x = 0;
    if (rect.pos.y < 0)
        rect.pos.y = 0;
    rect.dir.x = rand() % 2 - 1;
    rect.dir.y = rand() % 2 - 1;


    for (int i = 0; i < 300; i++) {
        sh1106_fill(buffer, 0x00);
        update_rectangle(&rect);
        sh1106_draw_rect(buffer, rect.pos.x, rect.pos.y, 
                         rect.width, rect.height, 1);
        sh1106_update_screen(sh1106_fd, buffer);
    }

    sh1106_turnoff(sh1106_fd);
    close(sh1106_fd);

    return status;
}


void update_rectangle(struct rectangle_ *rect)
{
    if (rect->dir.x > 0) {
        if (rect->pos.x + rect->width >= SH1106_WIDTH) {
            rect->dir.x = -1;
        }
    }
    else {
        if ( rect->pos.x <= 0) {
            rect->dir.x = 1;
        }
    }
    rect->pos.x += rect->dir.x;
    if (rect->dir.y > 0) {
        if (rect->pos.y + rect->height >= SH1106_HEIGHT) {
            rect->dir.y = -1;
        }
    }
    else {
        if ( rect->pos.y <= 0) {
            rect->dir.y = 1;
        }
    }
    rect->pos.y += rect->dir.y;
}
