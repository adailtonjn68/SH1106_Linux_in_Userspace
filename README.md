# SH1106_Linux_in_Userspace

## General description
This library is used to open a device driver as a file descriptor in Linux Userspace.
Also, there are functions to save the buffers as images.

## Source files description
sh1106_driver.c -> implements the writing and reading of the module.

sh1106_draw.c -> implements drawing functions such as 
* Rectangle
* Filled Rectangle
* Lines
* Circle

sh1106_file_io.c -> implements the export functions to save the buffers as images. In the future it will have functions to read images too.

## Other comments

In the folder Examples there are use cases of the functions implemented.

Be aware that the system was tested in a Raspberry Pi 3 with an I2C SH1106 (132x64) display. 
