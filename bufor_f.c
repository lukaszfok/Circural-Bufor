#include <string.h>
#include "bufor.h"

void circbuf_init(buf * b, char *tekst, int len)
{	
	b->len = len;	
	b->recent_buffer_write = 0;
	b->recent_buffer_read = 0;
	b->recent_buffer_overlap = 0;
}
void w_byte(buf * b, char byte)
{
	if(b->recent_buffer_overlap == 1){
		b->recent_buffer_read++;
		if(b->recent_buffer_read == b->len){
			b->recent_buffer_read = 0;
		}
		b->recent_buffer_overlap = 0;			
	}
	
	
	b->circ_buf[b->recent_buffer_write++] = byte;
	
	if(b->recent_buffer_write >= b->len){
		b->recent_buffer_write = 0;
	}
	
	if(b->recent_buffer_write == b->recent_buffer_read){
		b->recent_buffer_overlap = 1;
		//buf->r++;
		//if(buf->r == buf->len){
		//	buf->r = 0;
		//}			
	}	
	//printf("W%d R%d\n",buf->w,buf->r );	
}

int r_byte(buf * b, char *byte)
{
	if(b->recent_buffer_overlap){
		b->recent_buffer_overlap = 0;	
	}else{
	
		if(b->recent_buffer_write == b->recent_buffer_read){
			return 0;
		}
	}
	*byte = b->circ_buf[b->recent_buffer_read++];
	if(b->recent_buffer_read == b->len){
		b->recent_buffer_read = 0;
	}
	return 1;	
}

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
		b->circ_buf[b->recent_buffer_write] = tekst[i];
		if(b->recent_buffer_write == b->recent_buffer_read && b->recent_buffer_overlap){
			b->recent_buffer_read++;

		}
		if(b->recent_buffer_read>=sizeof(b->circ_buf)){
			b->recent_buffer_read=0;
		}
		b->recent_buffer_write++;
		if(b->recent_buffer_write >= sizeof(b->circ_buf)){
	  		b->recent_buffer_write=0;
	  		b->recent_buffer_overlap =1;
		}
		
    	
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

	for(i = 0; i < length && (b->recent_buffer_read!=b->recent_buffer_write || b->recent_buffer_overlap); i++){		
      tekst[i] = b->circ_buf[b->recent_buffer_read]; 
      b->recent_buffer_read++;
      	
	if(b->recent_buffer_read >=sizeof(b->circ_buf)){
			b->recent_buffer_read=0;
			b->recent_buffer_overlap =0;
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
	//printf("a\n");
	int sign_state = get_sign_index(b,sign);
	//printf("%d\n ",sign_state);
	int count = 0;
	if(sign_state == -1){
		return 0;
	}
					
	for(i=b->recent_buffer_read; i < length && b->recent_buffer_read != sign_state; i++){
		tekst[count] = b->circ_buf[b->recent_buffer_read++];
		count++;
			
		if(b->recent_buffer_read >sizeof(b->circ_buf)){
				b->recent_buffer_read=0;
		}
		
	}
	tekst[count] = '\0';
	b->recent_buffer_read+=1;		
	return count;
}
int get_sign_index(buf *b, char sign){
	unsigned int i;
	for(i=b->recent_buffer_read; i != b->recent_buffer_write; i++){ 	
		//printf("%d\n ",i);
		if(i > sizeof(b->circ_buf)){
				i = 0;
		}
		//printf("%d\n ",i);
		if(b->circ_buf[i] == sign){

			return i;
		}	
	}
	return -1;	
} 
