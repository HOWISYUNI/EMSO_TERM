#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../lib/KSF_NET/ksf_net_lib.h"


int main(void){
    int sock, c_sock, ret;
    struct request *req;
    int count = 0;

    sock = server_open(LOCAL_PORT);
    if(sock < 0){
        printf("fail init socket\n");
        return -1;
    }
    req = (struct request*)malloc(sizeof(struct request));
    memset(req, 0, sizeof(struct request));
    while(1){
    c_sock = wait_request(sock, req);
    count++;
    printf("req.method : %c\n", req->method);
    printf("req.type : %c\n", req->type);
    printf("req.cmd : %c\n", req->cmd);
    printf("req.len : %ld\n", req->len);
    printf("req.data : %s\n", req->data);
    
    if(c_sock < 0){
        printf("fail get request\n");
        return -1;
    }
    ret = response(c_sock, 's', count, "hello\n");
    if(ret < 0){
        printf("fail response\n");
        return -1;
    }
    }
    free(req);
    server_close(sock);
    return 0;
}
