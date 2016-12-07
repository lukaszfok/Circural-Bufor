#include <string.h>
#include "bufor.h"

static char circ_buf[512];
int i;

int my_write(char *tekst, size_t length){
	for(int i = 0; i < length; i++ ){
      circ_buf[i] = tekst[i];
      }
	return i;
}

int my_read(char *tekst, size_t length){
	for(int i = 0; i < length; i++ ){
      tekst[i] = circ_buf[i];
      }
	return i;
}

