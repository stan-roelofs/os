#ifndef _DRIVERS_PORTS_H
#define _DRIVERS_PORTS_H

unsigned char port_byte_in(unsigned short port);
unsigned char port_byte_out(unsigned short port, unsigned char data);
unsigned char port_word_in(unsigned short port);
unsigned char port_wordout(unsigned short port, unsigned short data);

#endif