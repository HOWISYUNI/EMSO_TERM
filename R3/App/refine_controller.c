#include <unistd.h>
#include <stdio.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(void){
	int srv;		/* srv = server sock */
	int c_sock;		/* client server sock */

	//struct response rsp;
	struct request *req;

	unsigned long data_len;
	char *data;

	req = (struct request*)malloc(sizeof(struct request));
	//data = (char*)malloc(BUFF_SIZE);

	srv = server_open(R3_REF_PORT);		//3020
	while(1){
		printf("Wait!!\n");
		c_sock = wait_request(srv, req);
		printf("type : %c\n", req->type);
		printf("cmd : %c\n", req->cmd);

		sleep(1);
		if(req->method == 'G'){
			printf("Come here!!\n");
			//refine_data(req->type, req->cmd, data);
			//refine_data('l', 'v', data);
			data = refine_data(req->type, req->cmd, req->data);
			
			printf("data : %s\n", data);
			data_len = strlen(data);
			printf("data_len : %ld\n", data_len);

			response(c_sock, 's', data_len, data);
			printf("succes to send!!\n");
		}
		else{
			response(c_sock, 'f', 0, "Failed not refine");
			printf("Fail to send!!\n");
		
		}
		sleep(3);
	}
	free(req);
	free(data);
	server_close(srv);
	
	return 0;
}
