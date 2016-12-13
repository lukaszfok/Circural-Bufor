#include <string.h>
#include "bufor.h"

static char circ_buf[30];
static int recent_buffer_write;
static int recent_buffer_read;

int my_write(char *tekst, size_t length){
	int i;
	for(i = 0; i < length; i++ ){
		if(recent_buffer_write > sizeof(circ_buf)){
	  		recent_buffer_write=0;
		}
		if(recent_buffer_write+1 == recent_buffer_read){
			recent_buffer_read++;
		}
		if(recent_buffer_read>sizeof(circ_buf)){
			recent_buffer_read=0;
		}
    	circ_buf[recent_buffer_write++] = tekst[i];
    } 
	recent_buffer_write=recent_buffer_write % sizeof(circ_buf);
	return i;
}

int my_read(char *tekst, size_t length){
	int i;
	for(i = 0; i < length && recent_buffer_read<recent_buffer_write; i++){
      tekst[i] = circ_buf[recent_buffer_read++]; 
      
	if(recent_buffer_read >sizeof(circ_buf)){
			recent_buffer_read=0;

		}	
}
	return i;
}
