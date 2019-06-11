#include "ksf_net.h"

int client_open(char *dest_ip, int port);
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);
int client_close(int sock);
