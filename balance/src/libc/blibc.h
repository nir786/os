#ifndef B_LIBC_H
#define B_LIBC_H

#include <stdint.h>
uint8_t inb ( uint16_t port);
//take char from port

void outb(uint16_t port, uint8_t val); 
//put char in port

void init_serial();
//init reading

void serial_write(char c);
//write to port

void serial_write_stirng(char* string); 


void serial_write_hex(uint64_t hex);







#endif // !B_LIBC_H
