#include <stdint.h>
#include <stddef.h>
#include "../libc/blibc.h"
#include "../includes/limine.h"
__attribute__((section(".limine_reqs")))
static volatile LIMINE_BASE_REVISION(3);



__attribute__((used,section(".limine_reqs")))
volatile struct limine_framebuffer_request fb_req ={
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0 
};

__attribute__((used,section(".limine_reqs")))
volatile struct limine_memmap_request memap_req ={
  .id =LIMINE_MEMMAP_REQUEST,
  .revision =0
};


__attribute__((used,section(".limine_reqs")))
volatile struct limine_hhdm_request hhdm_req = {
.id = LIMINE_HHDM_REQUEST,
.revision = 0 

};


__attribute__((used,section(".limine_reqs")))
volatile struct limine_kernel_address_request kaddr_req= {
  .id = LIMINE_KERNEL_ADDRESS_REQUEST,
  .revision = 0 
};





uint64_t get_cr3(void){
  uint64_t cr3; 
__asm__ volatile ("mov %%cr3, %0":"=r"(cr3)); 
  return cr3 ; 
}
uint64_t read_cr0(){

uint64_t val; 
  __asm__ volatile ("mov %%cr0, %0": "=r"(val)); 


  return val ; 

}

typedef struct {
uint64_t base ; 
uint64_t lenght;
}mem_section; 
uint64_t sections_count ( ){
uint64_t count = 0 ; 
for(uint64_t i =0 ; i < memap_req.response->entry_count;i ++){
if(memap_req.response->entries[i]->type == 1)count++; 
  }

return count; 
}

mem_section sections[32] ; 
void usable_sections ( ){
int sec_count; 

  for(uint64_t i =0 ; i < memap_req.response->entry_count;i ++){
if(memap_req.response->entries[i]->type == 1){
sections[sec_count].base = memap_req.response->entries[i]->base ; 
sections[sec_count].lenght= memap_req.response->entries[i]->length ; 
serial_write_hex(sections[sec_count].base); 
serial_write_hex(sections[sec_count].lenght); 
serial_write_stirng("for section number"); 
serial_write_hex((uint64_t)sec_count); 
    sec_count++; 
    } 
  }

}


void kernel_main(void){
init_serial();
uint64_t dogshit = sections_count(); 
usable_sections(); 
  while(1){
    __asm__ volatile ("hlt"); 
  }
}
