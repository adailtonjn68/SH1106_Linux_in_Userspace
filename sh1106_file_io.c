#include "sh1106_file_io.h"
#include <stdio.h>


#define SH1106_WIDTH 132
#define SH1106_HEIGHT 64


int sh1106_file_export_to_pbm(const char *const filename,
                              const uint8_t *const buffer)
{
    FILE *file_ = fopen(filename, "w");
    if (file_ == NULL) {
        printf("Not possible to open file %s\n", filename);
        return 1;
    }

    fprintf(file_, "P1\n%d %d\n", SH1106_WIDTH, SH1106_HEIGHT);
    for (int16_t y = 0; y < SH1106_HEIGHT; y++) {
        int16_t temp1 = (int16_t) ((y / 8)* SH1106_WIDTH) ;
        int16_t temp2 = 1 << (y % 8);
        for (int16_t x = 0; x < SH1106_WIDTH; x++) {
            /* Write 0 for white pixel and 1 for black */
            fprintf(file_, "%d ", !((buffer[x + temp1] & temp2) > 0));
        }
        fprintf(file_, "\n");
    }

    fclose(file_);

    return 0;
}


int sh1106_file_export(const char *const filename, 
                       const uint8_t *const buffer)
{
    int ret = 0;

    ret = sh1106_file_export_to_pbm(filename, buffer);

    return ret;
}

