#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

void one_read_one_write();
void few_write_one_read();
void few_write_few_read();
void critical_error_test();
/*static buf b;*/

int main()
{  		
	
	one_read_one_write();

	few_write_one_read();

	few_write_few_read();

	critical_error_test();
		
	
    return 0;
}
