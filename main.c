#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

int main()
{  		
	char tekst[30];
	int state;

	my_write("down",4);
	my_write("load",4);
	my_write("pullup",6);
	my_write("trololo",8);

	state = my_read(tekst,3);
	for(int i=0; i<state; i++){
		printf("%c", tekst[i]);
		}
	printf("\n");
	state = my_read(tekst,7);
	for(int i=0; i<state; i++){
		printf("%c", tekst[i]);
		}
	printf("\n");

	my_read(tekst,sizeof(tekst));
	printf("%s\n", tekst);

    return 0;
}
