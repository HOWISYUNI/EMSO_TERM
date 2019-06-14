#include <stdio.h>
#include "../../lib/KSF_NET/ksf_net_lib.h"
int main(void){
    int sock, ret;
    struct response rsp;
    
    sock = client_open(LOCAL_HOST, LOCAL_PORT, 5);
    printf("client open\n");
    
    rsp = request(sock, 'G', 'T', 'C', 100, "hi everyone\n");
    client_close(sock);

    sock = client_open(LOCAL_HOST, LOCAL_PORT, 5);    
    printf("rsp.type : %c\n", rsp.type);
    printf("rsp.len : %ld\n", rsp.len);
    printf("rsp.data : %s\n", rsp.data);

    rsp = request(sock, 'O', 'C', 'T', 101, "hi everyone\n");

    printf("rsp.type : %c\n", rsp.type);
    printf("rsp.len : %ld\n", rsp.len);
    printf("rsp.data : %s\n", rsp.data);

    client_close(sock);    

    return 0;
}
