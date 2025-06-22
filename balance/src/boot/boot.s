global _start
extern kernel_main 


section .text
_start: 
  cli
  mov rsp , stack_top
  call kernel_main

.hang:
hlt
jmp .hang


section .bss 
align 16 
stack_bottom:
  resb 0x4000
stack_top: 
