#include <stdio.h>
#include "ksf_net.h"

int server_open(int port);
int server_close(int sock);
int wait_request(int sock, struct request *req);
int response(int c_sock, char type, unsigned long len, char *data);


int main(void){
    int sock, c_sock, ret;
    struct request *req;
    
    sock = server_open(1010);
    if(sock < 0){
        printf("fail init socket\n");
        return -1;
    }
    c_sock = wait_request(sock, req);
    if(c_sock < 0){
        printf("fail get request\n");
        return -1;
    }
    ret = response(c_sock, 't', 100, "hello\n");
    if(ret < 0){
        printf("fail response\n");
        return -1;
    }
    
    server_close(sock);
    return 0;
}
