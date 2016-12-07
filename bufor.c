#include <stdio.h>
#include <stdlib.h>

#include "bufor.h"
#define Size_buf 20

int main()
{   int fd;
    int i;
    char buf[Size_buf];
    while(scanf("%s",buf)){
    if(strlen(buf) > 20){
        exit(-1);

    }else{
        my_write(fd,buf);
    }
}
    my_read(fd,buf);

    printf("%s",buf);

    return 0;
}
