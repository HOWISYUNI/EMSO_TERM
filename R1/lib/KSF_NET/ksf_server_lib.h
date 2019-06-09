#include "ksf_net.h"

/* INIT
 * */
int server_open(int port);
int server_close(int sock);
/* LISTEN
 * */
int wait_request(int sock, struct request *req);
/* RESPONSE
 * */
int response(int c_sock, char type, unsigned long len, char *data);
