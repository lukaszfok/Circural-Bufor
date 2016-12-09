#include <string.h>
#include "bufor.h"

static char circ_buf[512];
static int bufor_state;
static int end_bufor_state;

int my_write(char *tekst, size_t length){
	int i;
	for(i = 0; i < length; i++ ){
      circ_buf[i+bufor_state] = tekst[i];
      }
    bufor_state+=i;
	return i;
}

int my_read(char *tekst, size_t length){
	int i;
	for(i = end_bufor_state; i < bufor_state; i++){
      tekst[i] = circ_buf[i]; 
      }
    end_bufor_state+=i;
	return i;
}
