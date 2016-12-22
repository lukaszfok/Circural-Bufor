#include <string.h>
#include "bufor.h"



int my_write(buf *b,char *tekst, size_t length){

	unsigned int i;

	for(i = 0; i < length; i++ ){
		if(b->recent_buffer_write > sizeof(b->circ_buf)){
	  		b->recent_buffer_write=0;
		}
		if(b->recent_buffer_write+1 == b->recent_buffer_read){
			b->recent_buffer_read++;
		}
		if(b->recent_buffer_read>sizeof(b->circ_buf)){
			b->recent_buffer_read=0;
		}
    	b->circ_buf[b->recent_buffer_write++] = tekst[i];
    } 
	b->recent_buffer_write=b->recent_buffer_write % sizeof(b->circ_buf);
	return i;
}

int my_read(buf *b,char *tekst, size_t length){

	unsigned int i;

	for(i = 0; i < length && b->recent_buffer_read!=b->recent_buffer_write; i++){
      tekst[i] = b->circ_buf[b->recent_buffer_read++]; 
      
	if(b->recent_buffer_read >sizeof(b->circ_buf)){
			b->recent_buffer_read=0;
		}	
}
	return i;
}

int buffer_count(buf *b){

	if (b->recent_buffer_read <= b->recent_buffer_write)
		return b->recent_buffer_write - b->recent_buffer_read;
	
	return sizeof(b->circ_buf) - b->recent_buffer_read + b->recent_buffer_write;
}

void buffer_clear(buf *b){

	b->recent_buffer_write=b->recent_buffer_read=0;
}


