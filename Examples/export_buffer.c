#include <stdio.h>
#include <fcntl.h>      /* Needed to open I2C file descriptor */ 
#include <unistd.h>     /* Needed to close I2C file descriptor */
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "../sh1106_driver.h"
#include "../sh1106_draw.h"
#include "../sh1106_file_io.h"


unsigned char buffer[SH1106_SIZE];


int main(void)
{
    
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

    sh1106_fill(buffer, 0x00);
    sh1106_draw_rect_filled(buffer, 50, 20, 60, 30, 1);
    sh1106_draw_circle_filled(buffer, 50, 30, 40, 1);
    sh1106_draw_circle_filled(buffer, 50, 30, 10, 0);
    sh1106_draw_rect(buffer, 10, 10, 80, 10, 0);

    sh1106_update_screen(sh1106_fd, buffer);

    sh1106_file_export("./buffer.pbm", buffer);

    printf("Press ENTER\n");
    getchar();
    
    sh1106_turnoff(sh1106_fd);

    close(sh1106_fd);

    return status;
}
