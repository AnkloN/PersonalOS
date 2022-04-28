#include "util.h"
#include "./../libc/global_macros.h"


void memcpy_pos(char * source, char * dest, int bytes){
    int i;
    for(i=0;i<bytes;i++) *(dest + i) = *(source + i);
    return;
}

void int_to_ascii(int n, char str[]){
    int i = 0, sign = FALSE;
    if(n<0){
        sign = TRUE;
        n=-n;
    }
    do{
        str[i++] = n%10 + '0';
    }while((n/=10)>0);

    if(sign)str[i++]='-';
    str[i]='\0';
    return;
}