#include <stdio.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(void){
	int srv, clt;
	int c_sock;

	struct response rsp;
	struct request *req;

	unsigned long data_len;
	char *data = "";

	while(1){
		srv = server_open(3020);
		c_sock = wait_request(srv, req);

		if(req->method == 'G'){
			data = refine_data(req->type, req->cmd);
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
