#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"
/*!
* \brief Inicialization test
*	 Function for couse test for buffer
*/
void make_test2();
void one_read_one_write();
void few_write_one_read();
void few_write_few_read();
void critical_error_test();
void basic_util_read();
int until_read(buf *b,char *tekst,size_t length,char sign);

int main()
{  	
	make_test2();
	



	return 0;
}
