#ifndef BUFOR_H
#define BUFOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*!
* \brief All declarations
*	 File for declaration all function and structure.
*/
#define MAX_SIZE 30
/*!
* \brief Buffer structure
*	 Struct store table of buffer and index.
*/
typedef struct buffer{
char circ_buf[MAX_SIZE];
unsigned int recent_buffer_write;
unsigned int recent_buffer_read;
}buf;
/*!
* \brief Declaration logic function
*	 Declaration all logic function for buffer.
*/
int my_write(buf *b,char *tekst, size_t length);
int my_read(buf *b,char *tekst, size_t length);
int buffer_count(buf *b);
void buffer_clear(buf *b);
int until_read(buf *b,char *tekst,size_t length,char sign);
#endif
