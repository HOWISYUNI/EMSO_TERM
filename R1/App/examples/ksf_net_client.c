#include <stdio.h>

int client_open(char *dest_ip, int port);
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);
int client_close(int sock);

int main(void){
    int sock, ret;
    struct response rsp;
    
    sock = client_open(LOCAL_HOST, LOCAL_PORT);
    printf("client open\n");
    
    rsp = request(sock, 'G', 'T', 'C', 100, "hi everyone\n");
    
    printf("rsp.type : %c\n", rsp.type);
    printf("rsp.len : %ld\n", rsp.len);
    printf("rsp.data : %s\n", rsp.data);
    client_close(sock);    

    return 0;
}
