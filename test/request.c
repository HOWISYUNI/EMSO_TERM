#include <string.h>
#include "ksf_net_lib.h"

int main(int argc, char* argv[]){
    int sock, ret;
    struct response rsp;
    char method, type, cmd;
    unsigned long len;
    char data[BUFF_SIZE];
    int port;

    printf("agrc : %d\n", argc);
    if(argc == 7){
        method = argv[1][0];
        type = argv[2][0];
        cmd = argv[3][0];
        len = argv[4][0];
        strcpy(data, argv[5]);
        port = atoi(argv[6]);

        sock = client_open(LOCAL_HOST, port);
        printf("client open\n");
        printf("method : %c\n", method);
        printf("type : %c\n", type);
        printf("cmd : %c\n", cmd);
        printf("len :%ld\n", len);
        printf("data : %s\n", data);  
        printf("port : %d\n", port);

        rsp = request(sock, method, type, cmd, len, data);
        
        printf("received\n");
        printf("rsp.type : %c\n", rsp.type);
        printf("rsp.len : %ld\n", rsp.len);
        printf("rsp.data : %s\n", rsp.data);
        client_close(sock);

        return 0;    
    }
    else{
        printf("not enough parameter, (char)Method | (char)Type | (char)Cmd | (unsigned long int)len | (char[1024])data\n");
        return 0;
    }  
}
