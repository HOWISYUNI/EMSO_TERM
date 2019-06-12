#include <stdio.h>

#include "../lib/ksf_server_lib.h"

int main(void){
	int srv, clt;
	int c_sock;
	struct response rsp;
	struct request req;
	unsigned long data_len;
	int data = 0;

	srv = server_open(R3_REF_PORT);
	//clt = client_open("127.0.0.1", 3020);

	while(1){
		srv = server_open(R3_REF_PORT);
		c_sock = wait_request(srv, req);

		if(req.method == 'G'){
			data = refine_data(req.type, req.cmd);
			data_len = strlen(data);

			response(c_sock, 's', data_len, data);
		}
		else{
			response(c_sock, 'f', 0, "Failed not refine");
		}
		server_close(srv);
	}

	return 0;
}
