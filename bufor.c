#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"
/*!
* \brief Inicialization test
*	 Function for couse test for buffer
*/
void one_read_one_write();
void few_write_one_read();
void few_write_few_read();
void critical_error_test();
int until_read(buf *b,char *tekst,size_t length,char sign);

int main()
{  		
	one_read_one_write();
	few_write_one_read();
	few_write_few_read();
	critical_error_test();

	read_until(NULL, 100, '\r');

    return 0;
}
