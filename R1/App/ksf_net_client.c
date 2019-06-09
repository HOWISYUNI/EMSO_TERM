#include <stdio.h>
#include "ksf_net.h"

int client_open(char *dest_ip, int port);
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);
int client_close(int sock);

int main(void){
    int sock, ret;
    struct response rsp;
    
    sock = client_open("127.0.0.1", 1010);
    printf("client open\n");
    
    rsp = request(sock, 'G', 'T', 'C', 100, "hi everyone\n");
    
    printf("rsp : %c %ld %s\n", rsp.type, rsp.len, rsp.data);
    client_close(sock);    

    return 0;
}
