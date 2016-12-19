#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"

int main()
{  		
	one_read_one_write();
	buffer_clear();
	few_write_one_read();
	buffer_clear();	
	few_write_few_read();

    return 0;
}
