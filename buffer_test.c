#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

void one_read_one_write(){
	
	char tekst[30];
	int write;
	int read;
	write = my_write("down",4);
	read = my_read(tekst,4);
	char tekst_in[] = "down";
	if(write!=read){
		printf("ERROR");
	}else{
		for(int i=0; i<write; i++){
		tekst[i]  tekst_in[i]
	}
}

void few_write_one_read(){

	char tekst[30];
	int write;
	int read;
	write = my_write("down",4);
	write = my_write("load",4);
	read = my_read(tekst,8);
	for(int i=0; i<write; i++){
		if(sizeof(write)!= sizeof(read)){
			printf("ERROR");
		}
		
	}
}
void few_write_few_read(){



}
void critical_error_test(){




}
