#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bufor.h"
#include "unit_test.h"




static int single_r_w(void);
static int read_empty(void);
static int xbytes_overlap(int bytes_overlap);
static int million_writes_single_read(void);

void make_test(void)
{
	
	int testresult;
	int i;
	printf("Starting test\n");

	testresult = read_empty();
	if(testresult){
		printf("Fail: %d\n",testresult);	
	}else{
		printf("Empty read OK\n");
	}
			
	testresult = single_r_w();
	if(testresult){
		printf("Fail: %d\n",testresult);	
	}else{
		printf("Single RW ok\n");
	}
	
	testresult = read_empty();
	if(testresult){
		printf("Fail: %d\n",testresult);	
	}else{
		printf("Empty read OK\n");
	}	
	
	for(i=1; i<MAX_SIZE-1; i++)
	{
		testresult = xbytes_overlap(i);
		if(testresult){
			printf("Fail[%i]: %d\n",i,testresult);	
		}else{
			printf("Single overlap %d OK\n",i);
		}
	}
	testresult = million_writes_single_read();
	if(testresult){
		printf("Fail: %d\n",testresult);	
	}else{
		printf("1M write OK\n");
	}		
}

/*
 Write 1 char. read 1 char
 Wthat I write is what I read
*/
static int single_r_w(void)
{
	int i;
	for (i=0; i<MAX_SIZE; i++){
		char tekst[30];
		int retval;
		int read_val;
		char testvalue = (char) i;
		char compare_value;
		
		retval = my_write(&testbuf,&testvalue, 1);
		if(retval != 1){
			return -1;
		}
		
		retval = my_read(&tekst, &compare_value, 1);
		if(retval != 1){
			return -1;
		}
		if(testvalue != compare_value ){
			printf("Fail: %d != %d\n",testvalue,compare_value );	
			return -2;			
		}		
		//printf("OK: %d == %d\n",testvalue,compare_value );				
	}
	return 0;	
}

/*
 Return 0 is buffer is empty( must be empty)
*/
static int read_empty(void)
{
	char compare_value;
	int retval;
	retval = my_read(&testbuf, &compare_value, 1);
	
	if(retval == 1){
		printf("Fail: %d\n",compare_value );
		return -1;
	}
	return 0;
}

/*
 Write size + 1 starting from 0
 Read '1'
 
 INIT: R=0, W=0
 FULL: R=0 W = 0 (buffer fully written)
 OVERLAP: W=1, R=1 (read moves to the oldest existing)
 ADD NEXT BYTE: W=2, R=2 (read moves one byte)
 
 R always point to the the oldest, wrap around is a return value or some kind of flag
 
 
*/
static int xbytes_overlap(int bytes_overlap)
{
	int i;
	int read_val;
	int retval;
	char compare_value;

	/* remove any history operations
	*/
	memset(&testbuf, 0, sizeof(buf));
	if(read_empty())
	{
			printf("Not empty\n");
			return -1;		
	}

	for (i=0; i < (MAX_SIZE + bytes_overlap);  i++){

		char testvalue = (char) i;
		
		retval = my_write(&testbuf,&testvalue, 1);
		if(retval != 1){
			printf("Fail writing index %d \n",i );
			return -1;
		}
	}
		
	retval = my_read(&testbuf, &compare_value, 1);
	if(retval != 1){
		printf("Fail reading returns %d \n",retval );
		return -1;
	}
	if(bytes_overlap != compare_value ){
		printf("Fail: %d != %d\n",bytes_overlap,compare_value );	
		return -2;			
	}		
		//printf("OK: %d == %d\n",testvalue,compare_value );				
	
	return 0;
}


/*
 Write 1M chars
 Read just one of them.
*/
static int million_writes_single_read(void)
{
	int i;
	int read_val;
	int retval;
	char compare_value;

	/* remove any history operations
	*/
	memset(&testbuf, 0, sizeof(buf));
	if(read_empty())
	{
			printf("Not empty\n");
			return -1;		
	}

	for (i=0; i<1000000; i++){

		char testvalue = (char) i;
		
		retval = my_write(&testbuf,&testvalue, 1);
		if(retval != 1){
			printf("Fail writing index %d \n",i );
			return -1;
		}
	}
		
	retval = my_read(&testbuf, &compare_value, 1);
	if(retval != 1){
		printf("1M Fail reading returns %d \n",retval );
		return -1;
	}
	
		//printf("OK: %d == %d\n",testvalue,compare_value );				
	printf("Read: %d \n",compare_value );
	return 0;
}



