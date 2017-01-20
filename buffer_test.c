#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"
/*!
* \brief All function for test buffer data 
*/
char* check_data(char* tekst,char* tekst_in, int read, int write);
void one_read_one_write();
void few_write_one_read();
void few_write_few_read();
void critical_error_test();
void basic_util_read();


/*!
* \brief Function one write one read
*	 Function check data currect for buffer use one write data and one read data with buffor
*/
void one_read_one_write()
{
	char tekst[30];
	int write;
	int read;
	buf b;
	write = my_write(&b,"down", 4);
	read = my_read(&b,tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "down", read, write));
}
/*!
* \brief Function few write one read
*	 Function check data currect for buffer use few write data and one read data with buffor
*/
void few_write_one_read()
{
	char tekst[30];
	int write;
	int read;
	buf b;
	write = my_write(&b,"down", 4);
	write += my_write(&b,"load1", 5);
	read = my_read(&b,tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "download1", read, write));
}
/*!
* \brief Function few write few read
*	 Function check data currect for buffer use few write data and few read data with buffor
*/
void few_write_few_read()
{
	char tekst[30];
	int write;
	int read;
	buf b;
	write = my_write(&b,"down", 4);
	write += my_write(&b,"load1", 5);
	read = my_read(&b,tekst, 3);
	read += my_read(&b,tekst + read, sizeof(tekst) - read);
	printf("%s\n", check_data(tekst, "download1", read, write));
}
/*!
* \brief Function critical error
*	 Function check data currect for buffer when in buffer write a lot of data
*/
void critical_error_test()
{
	buf b;
	char tekst[30];
	int write = my_write(&b,"1234567890123456789012", 22);
	int read = my_read(&b,tekst, sizeof(tekst));
	
	printf("%s\n", check_data(tekst, "1234567890123456789012", read, write));

	write = my_write(&b,"123", 3);
	read = my_read(&b,tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "123", read, write));
}
/*!
*	\brief Test Until Read
*
*/
void basic_util_read()
{
	buf b;
	int write;
	int read_u; 
	char tekst[30];
	buffer_clear(&b);
	write = my_write(&b,"1234567890",11);		
	read_u = until_read(&b,tekst,30,'\r');
	printf("%d\n",read_u);
	
	buffer_clear(&b);
	write = my_write(&b,"1234567890\x1B",14);		
	read_u = until_read(&b,tekst,30,'\x1B');
	printf("%d %s\n",read_u ,tekst);
	
	buffer_clear(&b);
	write = my_write(&b,"1234567890\x1B",14);		
	read_u = until_read(&b,tekst,30,'\x1B');
	printf("%d %s\n",read_u ,tekst);
	
	buffer_clear(&b);
	write = my_write(&b,"1234567\r901234\r",16);		
	read_u = until_read(&b,tekst,30,'\r');
	printf("%d %s\n",read_u ,tekst);
	read_u = until_read(&b,tekst,30,'\r');
	printf("%d %s\n",read_u ,tekst);
}
/*!
* \brief Function check
*	 Function check correct data.
*/
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

