#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

int main()
{  		
 	char tekst[512];
    while(scanf("%s",tekst)){
    
    if(strlen(tekst) == 512){
        exit(-1);
    }else{
        my_write(tekst,strlen(tekst));
    }
    my_read(tekst,strlen(tekst));
	printf("%s\n",tekst);
}
    return 0;
}
