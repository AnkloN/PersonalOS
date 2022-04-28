#include "util.h"
#include "./../libc/global_macros.h"


void memcpy_pos(char * source, char * dest, int bytes){
    int i;
    for(i=0;i<bytes;i++) *(dest + i) = *(source + i);
    return;
}

void memset_pos(uchar_8* dest, uchar_8 value, uint_32 length){
    uchar_8 * temp = (uchar_8*)dest;
    for(;length!=0;length--)*(temp++) = value;

}
int strlen(char s[]){
    int i =0;
    while (s[i]!='\0')i++;
    return i;    
}

void reverse(char s[]){
    int ch, i,j;
    for(i=0,j=strlen(s)-1;i<j;i++,j--){
        ch = s[i];
        s[i]=s[j];
        s[j]=ch;
    }
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
    reverse(str);
}

