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
unsigned int len;
unsigned int recent_buffer_write;
unsigned int recent_buffer_read;
unsigned int recent_buffer_overlap;
}buf;
/*!
* \brief Declaration logic function
*	 Declaration all logic function for buffer.
*/
void make_test2(void);
int my_write(buf *b,char *tekst, size_t length);
int my_read(buf *b,char *tekst, size_t length);
int buffer_count(buf *b);
void buffer_clear(buf *b);
int until_read(buf *b,char *tekst,size_t length,char sign);
int get_sign_index(buf *b, char sign);
void circbuf_init(buf * b, char *tekst, int len);
void w_byte(buf * b, char byte);
int r_byte(buf * b, char *byte);
#endif
