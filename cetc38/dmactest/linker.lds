MEMORY
{
  SHARED_PROG(rx)  		: ORIGIN = 0x0,      LENGTH = 96K     /*片内共享程序存储器*/
  LOCAL_SRAM(rx)   		: ORIGIN = 0xe20000, LENGTH = 64K     /*核内私有程序存储器*/   
  DATA0(rw)  	 	  	: ORIGIN = 0x200000, LENGTH = 256K     
  DATA1(rw)				: ORIGIN = 0x400000, LENGTH = 256K     	 
  DATA2(rw)  			: ORIGIN = 0x600000, LENGTH = 256K     
  DATA3(rw)  		 	: ORIGIN = 0x800000, LENGTH = 256K    
  DATA4(rw)  		 	: ORIGIN = 0xA00000, LENGTH = 256K    
  DATA5(rw)  		 	: ORIGIN = 0xC00000, LENGTH = 262142  /*保留2个字,加载核使用*/
  DEBUG_INFO       		: ORIGIN =0x0,       LENGTH = 25600K  
  DEBUG_ARANGES    		: ORIGIN =0x0 ,      LENGTH = 25600K
  DEBUG_PUBNAMES   		: ORIGIN =0x0 ,      LENGTH = 25600K
  DEBUG_LINE       		: ORIGIN =0x0 ,      LENGTH = 25600K
  DEBUG_ABBREV     		: ORIGIN =0x0 ,      LENGTH = 25600K
  DEBUG_STR				: ORIGIN =0x0,	     LENGTH = 25600K
}

SECTIONS
{
   .text :
  {
     *(.text)
  } > SHARED_PROG
  .data :
  {
		*(.data)
   }  > DATA0
   .bss :
   {
   ____bss_start = . ;
   	*(.bss)
   ____bss_end = . ;
   }  > DATA0
   .debug_info :
  {
    *(.debug_info)
  } > DEBUG_INFO
  .debug_aranges : 
  {
    *(.debug_aranges)
  } > DEBUG_ARANGES
  .debug_pubnames :
  {
    *(.debug_pubnames)
  } > DEBUG_PUBNAMES
  .debug_line :
  {
    *(.debug_line)
  } > DEBUG_LINE
  .debug_abbrev :
  {
     *(.debug_abbrev)
  } > DEBUG_ABBREV
  
  .debug_str :
  {
    *(.debug_str)
  } > DEBUG_STR
  
 } 


