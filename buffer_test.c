#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

void one_read_one_write(){
	
	char tekst[30];
	int write;
	int read;
	char tekst_in[]="down";
	write = my_write("down",4);
	read = my_read(tekst,4);
	
	printf("%s %d %d\n",check_state(tekst,tekst_in,write,read),write,read);		
}
void few_write_one_read(){
	char tekst[30];
	int write;
	int read;
	int state;
	
	char tekst_in[]="download";
	write = my_write("down",4);
	state = write;
	write = my_write("load",5);
	read = my_read(tekst,9);
	
	printf("%s %d %d\n",check_state(tekst,tekst_in,write+state,read),write+state,read);

}
void few_write_few_read(){
	char tekst[30];
	int write;
	int read;
	char tekst_in[]="download";
	write = my_write("down",4);
	
	write = my_write("load",5);
	
	read = my_read(tekst, 5);
	read += my_read(tekst + read, sizeof(tekst) - read);
	printf("%s %d %d\n",check_state(tekst,tekst_in,write,read),write,read);
	
	read = my_read(tekst, 4);
	read += my_read(tekst + read, sizeof(tekst) - read);
	printf("%s %d %d\n",check_state(tekst,tekst_in,write,read),write,read);
}
void critical_error_test(){

}

int check_state(char* tekst, char* tekst_in, int write, int read){
	if(write!=read){
		return "ERROR\n";
	}
	for(int i=0;i<write;i++){
		if(tekst[i]!=tekst_in[i]){
			return "ERROR\n";
		}
	}
	return "OK\n";	
}
