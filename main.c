	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "bufor.h"

int main()
{  		
	
	one_read_one_write();

	few_write_one_read();

	few_write_few_read();

	critical_error_test();
		
	
    return 0;
}
