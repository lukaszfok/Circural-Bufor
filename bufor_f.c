#include "bufor.h"

int my_write(int file, char *buf){

    return write(file, buf, strlen(buf)+1);
}

int my_read(int file, char *buf){

    return read(file, buf, strlen(buf)+1);
}

