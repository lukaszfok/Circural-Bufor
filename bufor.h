#ifndef BUFOR_H
#define BUFOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

typedef struct buffer{
char circ_buf[MAX_SIZE];
unsigned int recent_buffer_write;
unsigned int recent_buffer_read;
}buf;



int my_write(buf *b,char *tekst, size_t length);
int my_read(buf *b,char *tekst, size_t length);
int buffer_count(buf *b);
void buffer_clear(buf *b);


#endif
