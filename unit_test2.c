#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bufor.h"

int single_r_w(void);
int read_empty(void);
int xbytes_overlap(int bytes_overlap);
int million_writes_single_read(void);

void one_read_one_write(void);
void few_write_one_read(void);
void few_write_few_read(void);
void critical_error_test(void);
void basic_util_read(void);
buf b;

void make_test2(void)
{
	int testresult;
	int i;
char tekst[30];
	printf("Starting test buffor\n");

	circbuf_init(&b, tekst, MAX_SIZE);
	
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
		printf("Single RW OK\n");
	}
	
	/*testresult = read_empty();
	if(testresult){
		printf("Fail: %d\n",testresult);	
	}else{
		printf("Empty read OK\n");
	}	
	*/
	for(i=0; i<MAX_SIZE-1; i++)
	{
		testresult = xbytes_overlap(i);
		if(testresult){
			printf("Fail[%i]: %d\n",i,testresult);	
		}else{
			printf("Single overlap %d OK\n",i);
		}
	}
	//testresult = million_writes_single_read();
	if(testresult){
		printf("Fail: %d\n",testresult);	
	}else{
		printf("1M write OK\n");
	}	
		
	one_read_one_write();
	few_write_one_read();
	few_write_few_read();
	critical_error_test();
	basic_util_read();	
	
}

/*
 Write 1 char. read 1 char
 Wthat I write is what I read
*/
int single_r_w(void)
{
	int i;
	for (i=0; i<MAX_SIZE; i++){
		int retval;
		int read_val;
		char testvalue = (char) i;
		char compare_value;
		
		my_write(&b,&testvalue, 1);

		retval = my_read(&b, &compare_value, 1);
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
int read_empty(void)
{
	char compare_value;
	int retval;

	retval = my_read(&b, &compare_value, 1);

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
int xbytes_overlap(int bytes_overlap)
{
	int i;
	int read_val;
	int retval;
	char compare_value;
	char tekst[30];
	/* remove any history operations
	*/
	circbuf_init(&b, tekst, MAX_SIZE);
	
	if(read_empty())
	{
			printf("Not empty\n");
			return -1;		
	}

	for (i=0; i < (MAX_SIZE + bytes_overlap);  i++){

		char testvalue = (char) i;
		
		my_write(&b,&testvalue, 1);
		printf("%d %d %d\n",b.circ_buf[0],b.recent_buffer_write,b.recent_buffer_read);
	}
		
	retval = my_read(&b, &compare_value, 1);
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
int million_writes_single_read(void)
{
	int i;
	int read_val;
	int retval;
	char compare_value;
	buf b;
	char circ_buf;
	/* remove any history operations
	*/
	circbuf_init(&b, circ_buf, MAX_SIZE);
	if(read_empty())
	{
			printf("Not empty\n");
			return -1;		
	}

	for (i=0; i<1000000; i++){

		char testvalue = (char) i;
		
		my_write(&b,&testvalue, 1);
	}
		
	retval = my_read(&b, &compare_value, 1);
	if(retval != 1){
		printf("1M Fail reading returns %d \n",retval );
		return -1;
	}
	
		//printf("OK: %d == %d\n",testvalue,compare_value );				
	printf("Read: %d \n",compare_value );
	return 0;
	
}



////////////////////////////
char* check_data(char* tekst, char* tekst_in, int read, int write);



/*!
* \brief Function one write one read
*	 Function check data currect for buffer use one write data and one read data with buffor
*/
void one_read_one_write(void)
{
	char tekst[30];
	int write = 4;
	int read;
	buf b;
	circbuf_init(&b, tekst, MAX_SIZE);
	my_write(&b,"down", 4);
	read = my_read(&b,tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "down", read, write));
}
/*!
* \brief Function few write one read
*	 Function check data currect for buffer use few write data and one read data with buffor
*/
void few_write_one_read(void)
{
	char tekst[30];
	int write = 9;
	int read;
	buf b;
	circbuf_init(&b, tekst, MAX_SIZE);
	my_write(&b,"down", 4);
	my_write(&b,"load1", 5);
	read = my_read(&b,tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "download1", read, write));

}
/*!
* \brief Function few write few read
*	 Function check data currect for buffer use few write data and few read data with buffor
*/
void few_write_few_read(void)
{
	char tekst[30];
	int write =9;
	int read;
	buf b;
	circbuf_init(&b, tekst, MAX_SIZE);
	my_write(&b,"down", 4);
	my_write(&b,"load1", 5);
	read = my_read(&b,tekst, 3);
	read += my_read(&b,tekst + read, sizeof(tekst) - read);
	printf("%s\n", check_data(tekst, "download1", read, write));
}
/*!
* \brief Function critical error
*	 Function check data currect for buffer when in buffer write a lot of data
*/
void critical_error_test(void)
{
	char tekst[30];
	
	int write =22;
	int read;
	buf b;
	circbuf_init(&b, tekst, MAX_SIZE);
	write = 22;
	my_write(&b,"1234567890123456789012", 22);
	read = my_read(&b,tekst, sizeof(tekst));
	
	printf("%s\n", check_data(tekst, "1234567890123456789012", read, write));

	write = 3;
	my_write(&b,"123", 3);
	read = my_read(&b,tekst, sizeof(tekst));
	printf("%s\n", check_data(tekst, "123", read, write));
}
/*!
*	\brief Test Until Read
*
*/
void basic_util_read(void)
{
	int write;
	int read_u; 
	char tekst[30];
	buf b;
	circbuf_init(&b, tekst, MAX_SIZE);
	write = 11;
	my_write(&b,"1234567890",11);		
	read_u = until_read(&b,tekst,30,'\r');
	printf("%d\n",read_u);
	
	circbuf_init(&b, tekst, MAX_SIZE);
	write = 14;
	my_write(&b,"1234567890\x1B",14);		
	read_u = until_read(&b,tekst,30,'\x1B');
	printf("%d %s\n",read_u ,tekst);
	
	circbuf_init(&b, tekst, MAX_SIZE);
	write = 14;
	my_write(&b,"1234567890\x1B",14);		
	read_u = until_read(&b,tekst,30,'\x1B');
	printf("%d %s\n",read_u ,tekst);
	
	circbuf_init(&b, tekst, MAX_SIZE);
	write = 16;
	my_write(&b,"1234567\r901234\r",16);		
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
	int i;
	if (write != read) {
		return "ERROR";
	}

	for (i = 0; i < write; i++){
		if (tekst[i] != tekst_in[i]){
			return "ERROR";
		}
	}

	return "OK";
}
