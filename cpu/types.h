#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned int uint_32;
typedef unsigned short  uint_16;
typedef unsigned char   uchar_8;
typedef  int int_32;
typedef  short  int_16;
typedef  char   char_8;

// inline functinos
#define low_16b(address)(uint_16)((address) & 0xFFFF)
#define high_16b(address)(uint_16)((address >> 16) & 0xFFFF)



#endif