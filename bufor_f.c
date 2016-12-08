#include <string.h>
#include "bufor.h"

static char circ_buf[512];
static int bufor_state;

int my_write(char *tekst, size_t length){
	int i;
	for(i = 0; i < length; i++ ){
      circ_buf[i] = tekst[i];
      }
      bufor_state+=i;
	return i;
}

int my_read(char *tekst, size_t length){
	int i;
	for(i = 0; i < length; i++ ){
      tekst[i] = circ_buf[i]; 
      }
      bufor_state-=i;
	return i;
}
_media_work_122016
