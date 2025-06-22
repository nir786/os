

ENTRY (_start)

PHDRS
{
  limine_requests PT_LOAD;
  text PT_LOAD;
  rodata PT_LOAD;
  data PT_LOAD;


}

SECTIONS  {

. = 0xFFFFFFFF80000000; 
/*load and link to 0xFFFFFFFF80000000*/ 

.limine_requests : {
KEEP(*(.limine_request_start))
KEEP(*(.limine_request))
KEEP(*(.limine_request_end))
}:limine_requests


. = ALIGN(CONSTANT(MAXPAGESIZE)); 
.text : {
*(.text)
*(.text.*)
}

. = ALIGN(CONSTANT(MAXPAGESIZE)); 

.rodata : {
*(.rodata)
*(.rodata.*)
}

. = ALIGN(CONSTANT(MAXPAGESIZE)); 

.data : {
*(.data)
*(.data.*)
}

.bss : {
*(.bss)
*(.bss.*)
*(COMMON)
}

/DISCARD/ : {
  *(.eh_frame*)
  *(.note .note.*)
}




}
