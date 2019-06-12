#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024

#define R1_ADDR "10.10.10.13"
#define R1_SNR_PORT 1010  /* Client */
#define R1_ACT_PORT 1020  /* Server */
#define R2_ADDR "10.10.10.14"
#define R2_DATA_PORT 2010 /* Server */
#define R2_DATB_PORT 2010 /* Client */
#define R2_CMD_PORT 2020  /* Client */
#define R3_ADDR "10.10.10.15"
#define R3_STG_PORT 3010  /* Server */
#define R3_REF_PORT 3020  /* Server */
#define LOCAL_HOST "127.0.0.1"
#define LOCAL_PORT 4000

#ifndef _STRUCT_H_
#define _STRUCT_H_
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
#endif

/* Client Function */
int client_open(char *dest_ip, int port);
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);
int client_close(int sock);
/* Server Function */
int server_open(int port);
int server_close(int sock);
int wait_request(int sock, struct request *req);
int response(int c_sock, char type, unsigned long len, char *data);

