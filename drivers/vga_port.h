
#ifndef VGA_PORT
#define VGA_PORT

unsigned char port_byte_in ( unsigned short port);
void port_byte_out (unsigned short port, unsigned short data);
unsigned short port_word_in (unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

#endif