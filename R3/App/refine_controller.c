#include <stdio.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(void){
	int srv, clt;
	int c_sock;
	struct response rsp;
	struct request req;
	unsigned long data_len;
	int data = 0;
	char *data = "";

	//srv = server_open(R3_REF_PORT);
	//clt = client_open("127.0.0.1", 3020);

	while(1){
		srv = server_open(LOCAL_HOST);
		c_sock = wait_request(srv, req);

		if(req.method == 'G'){
			data = refine_data(req.type, req.cmd);
			data_len = strlen(abc);

			response(c_sock, 's', data_len, data);
		}
		else{
			response(c_sock, 'f', 0, "Failed not refine");
		}
		server_close(srv);
	}
	return 0;
}
