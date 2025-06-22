#include "blibc.h"
#include <stdint.h>



#define COM1 0x3F8

uint8_t inb ( uint16_t port){
uint8_t ret ; 
__asm__ volatile  ("inb %1, %0"
                    :"=a"(ret) 
                    :"Nd"(port));

return ret;  
}


void outb(uint16_t port, uint8_t val){ 
__asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port)); 
}

void init_serial(){
outb(COM1+1, 0x00);
outb(COM1+3, 0x80);
outb(COM1+0, 0x03);
outb(COM1+1, 0x00);
outb(COM1+3, 0x03);
outb(COM1+2, 0xC7);
outb(COM1+4, 0x0B);

}
void serial_write(char c){

  while(!(inb(COM1 +5 )& 0x20));
  outb(COM1, c);
}

void serial_write_stirng(char* string){

char c = string[0]; 
int char_point =0 ; 
while(c != '\0'){
serial_write(c);


char_point ++ ; 
c = string[char_point];      
  }
serial_write('\n');

}

void serial_write_hex(uint64_t hex){
  const char* hex_lookup = "0123456789ABCDEF"; 
   serial_write('0'); 
   serial_write('x'); 
  //fancy 

  for(int i = 60; i >= 0 ; i-= 4){
    char c = hex_lookup[(hex >> i)& 0xF]; 
    serial_write(c);
  }
   serial_write('\n');



}

