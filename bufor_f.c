#include <string.h>
#include "bufor.h"
/*!
* \brief Buffer logic
*/
/*!
* \brief Buffer write function
*	Function write data to buffer and moves index to last writes bytes.
*
*/
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
/*!
* \brief Buffer read functions
*	Function read bytes with buffer.
*/
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
/*!
* \brief Buffer cout
*  Function save data with buffer for read.
*/
int buffer_count(buf *b){

	if (b->recent_buffer_read <= b->recent_buffer_write)
		return b->recent_buffer_write - b->recent_buffer_read;
	
	return sizeof(b->circ_buf) - b->recent_buffer_read + b->recent_buffer_write;
}
/*!
* \brief Buffer clear
*  Function moves index to buffor start.
*/
void buffer_clear(buf *b){

	b->recent_buffer_write=b->recent_buffer_read=0;
}
/*!
* \brief Buffer until
* 
*/
int until_read(buf *b,char *tekst,size_t length,char sign){
		
	unsigned int i;
	int sign_state = -1;			
	for(i=b->recent_buffer_read; i != b->recent_buffer_write; i++){ 	
		if(i > sizeof(b->circ_buf)){
				i = 0;
		}
		if(b->circ_buf[i] == sign){
				sign_state = i;
		}
		
	}
	if(sign_state == -1){
		return 0;
	}
	
	for(i=0; i < length && b->recent_buffer_read != sign_state; i++){
		tekst[i] = b->circ_buf[b->recent_buffer_read++]; 
			
		if(b->recent_buffer_read >sizeof(b->circ_buf)){
				b->recent_buffer_read=0;
			}
		
	}
	b->recent_buffer_read=+2;		
	return i;
}
 
