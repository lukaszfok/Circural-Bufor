#ifndef BUFOR_H
#define BUFOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_write(char *tekst, size_t length);
int my_read(char *tekst, size_t length);
int buffer_count();
void buffer_clear(void);
char* check_data(char* tekst,char* tekst_in, int read, int write);
void one_read_one_write();
void few_write_one_read();
void few_write_few_read();
void critical_error_test();
#endif
