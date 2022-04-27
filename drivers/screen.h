/*
Our main video driver code
Gerular process will use this code to print output
*/

#ifndef __SCREEN_DRIVER_H__
#define __SCREEN_DRIVER_H__

// Information regarding VGA
#define REG_VGA_COTRL 0x3d4
#define REG_VGA_DATA 0x3d5
#define VGA_START_ADDR 0xb8000

#define VGA_MAX_ROWS 25
#define VGA_MAX_COLS 80
#define OFFSET_HIGH_BYTE 14
#define OFFSET_LOW_GYTE 15
// print color code 0xYZ where Y indicate background color and Z indicate font color
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define RED_ON_BLACK 0x04
#define BLACK_ON_GREEN 0xa0
#define BLACK_ON_PINK 0xd0
#define BLACK_ON_YELLOW 0xe0
// driver public functions
void clear_screen();
void kprint_at(char *data, int col, int row);
void kprint(void *data);

#endif