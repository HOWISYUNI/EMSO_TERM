#include "ksf_net.h"

int server_open(int port);
int server_close(int sock);
int wait_request(int sock, struct request *req);
int response(int c_sock, char type, unsigned long len, char *data);
