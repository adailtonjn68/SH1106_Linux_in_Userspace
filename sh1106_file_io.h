#ifndef SH1106_FILE_IO_H_
#define SH1106_FILE_IO_H_


#include <stdint.h>


int sh1106_file_export(const char *const filename,
                        const uint8_t *const buffer);
int sh1106_file_export_to_pbm(const char *const filename,
                              const uint8_t *const buffer);


#endif // SH1106_FILE_IO_H_
