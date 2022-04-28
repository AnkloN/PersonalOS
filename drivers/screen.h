/*
Our main video driver code
Gerular process will use this code to print output
*/

#ifndef __SCREEN_DRIVER_H__
#define __SCREEN_DRIVER_H__


// print color code 0xYZ where Y indicate background color and Z indicate font color
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4
#define RED_ON_BLACK 0x04
#define BLACK_ON_GREEN 0xa0
#define BLACK_ON_PINK 0xd0
#define BLACK_ON_YELLOW 0xe0
#define BLACK_ON_BLACK 0x00



// driver public functions
void clear_screen();
void clear_one_character();
void kline_break();
void kprint_at(char *data, int col, int row);
void kprint(void *data);

#endif