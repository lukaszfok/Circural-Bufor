#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"



void one_read_one_write()
{
	char tekst[30];
	int write;
	int read;

	write = my_write("down", 4);
	read = my_read(tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "down", read, write));
}

void few_write_one_read()
{
	char tekst[30];
	int write;
	int read;

	write = my_write("down", 4);
	write += my_write("load1", 5);
	read = my_read(tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "download1", read, write));
}

void few_write_few_read()
{
	char tekst[30];
	int write;
	int read;

	write = my_write("down", 4);
	write += my_write("load1", 5);
	read = my_read(tekst, 3);
	read += my_read(tekst + read, sizeof(tekst) - read);
	printf("%s\n", check_data(tekst, "download1", read, write));
}

void critical_error_test()
{
	char tekst[30];
	int write = my_write("1234567890123456789012", 22);
	int read = my_read(tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "1234567890123456789012", read, write));

	write = my_write("123", 3);
	read = my_read(tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "123", read, write));
}

char* check_data(char* tekst, char* tekst_in, int read, int write)
{
	if (write != read) {
		return "ERROR";
	}

	for (int i = 0; i < write; i++){
		if (tekst[i] != tekst_in[i]){
			return "ERROR";
		}
	}

	return "OK";
}

