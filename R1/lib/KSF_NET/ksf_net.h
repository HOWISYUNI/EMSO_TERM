#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

struct request{
    char method;
    char type;
    char cmd;
    unsigned long len;
    char data[BUFF_SIZE];
};

struct response{
    char type;
    unsigned long len;
    char data[BUFF_SIZE];
};
