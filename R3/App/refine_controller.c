#include <unistd.h>
#include <stdio.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(void){
	int srv;		/* srv = server sock */
	int c_sock;		/* client server sock */
	int flag;

	struct request *req;
	unsigned long data_len;
	char *data;

	req = (struct request*)malloc(sizeof(struct request));
	srv = server_open(R3_REF_PORT);		//3020

	while(1){
		printf("Wait for refining data!!\n");
		c_sock = wait_request(srv, req);
	
		flag = 0;
		if(req->method == 'G'){
			data = refine_data(req->type, req->cmd, req->data);
			if(strcmp(data, "fail0") == 0){
				flag = 1;
				printf("Wrong type!!\n");
				response(c_sock, 'f', 0, "Failed wrong type");
			}
			if(strcmp(data, "fail1") == 0){
				flag = 1;
				printf("Your data is too many than my txt file!!\n");
				response(c_sock, 'f', 0, "Your data is too many than my txt file");
			}
			if(strcmp(data, "fail2") == 0){
				flag = 1;
				printf("Wrong Cmd!!\n");
				response(c_sock, 'f', 0, "Failed wrong cmd");
			}

			if(flag == 0){
				printf("data : %s\n", data);
				data_len = strlen(data);
				printf("data_len : %ld\n", data_len);

				response(c_sock, 's', data_len, data);
				printf("succes to send!!\n");
			}
		}
		else{
			response(c_sock, 'f', 0, "Failed not refine");
			printf("Fail to send!!\n");
		}
		sleep(1);
	}
	free(req);
	free(data);
	server_close(srv);
	
	return 0;
}
