#include <string.h>
#include "bufor.h"

#define MAX_SIZE 30

static char circ_buf[MAX_SIZE];
static unsigned int recent_buffer_write;
static unsigned int recent_buffer_read;

int my_write(char *tekst, size_t length){

	unsigned int i;

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

	unsigned int i;

	for(i = 0; i < length && recent_buffer_read!=recent_buffer_write; i++){
      tekst[i] = circ_buf[recent_buffer_read++]; 
      
	if(recent_buffer_read >sizeof(circ_buf)){
			recent_buffer_read=0;
		}	
}
	return i;
}

int buffer_count(){
	if (recent_buffer_read <= recent_buffer_write)
		return recent_buffer_write - recent_buffer_read;
	
	return sizeof(circ_buf) - recent_buffer_read + recent_buffer_write;
}

void buffer_clear(void){
	
	recent_buffer_write=recent_buffer_read=0;
}


