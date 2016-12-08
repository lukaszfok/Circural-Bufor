#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

int main()
{  		
	char tekst[512];
	int state;

	my_write("down",4);
	my_write("load",4);

	my_read(tekst,3);
	printf("%s\n", tekst);

	my_read(tekst,sizeof(tekst));
	printf("%s\n", tekst);

    return 0;
}
