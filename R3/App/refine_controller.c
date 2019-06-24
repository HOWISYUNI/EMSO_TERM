#include <unistd.h>
#include <stdio.h>

#include "../../KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(void){
	int srv;		/* srv = server sock */
	int c_sock;		/* client server sock */
	int ret;

	struct request *req;
	unsigned long data_len;
	char *data;

	req = (struct request*)malloc(sizeof(struct request));
	srv = server_open(R3_REF_PORT);		//3020
	printf("R3.refine_controller init\n");

	while(1){
	    printf("wait request from R2.command_controller\n");
		c_sock = wait_request(srv, req);
	
		if(req->method == 'G'){
		    /* data refine */
			data = refine_data(req->type, req->cmd, req->data);
			
			/* exceptional case */
			if(strcmp(data, "fail0") == 0){
				printf("Wrong type!!\n");
				ret = response(c_sock, 'f', 0, "Failed wrong type");
			}
			else if(strcmp(data, "fail1") == 0){
				printf("Your data is too many than my txt file!!\n");
				ret = response(c_sock, 'f', 0, "Your data is too many than my txt file");
			}
			else if(strcmp(data, "fail2") == 0){
				printf("Wrong Cmd!!\n");
				ret = response(c_sock, 'f', 0, "Failed wrong cmd");
			}

            /* success refine data */
		    else {
			    data_len = strlen(data);
			    printf("[%ld]%s\n", data_len, data);
			    ret = response(c_sock, 's', data_len, data);
			    printf("succes to send!!\n");
		    }
		}
		else{
			printf("not support request method\n");
		    /* not support request method */
			ret = response(c_sock, 'f', 0, "not support request");
		}
		
		/* response failed */
		if(ret < 0){
	        printf("failed send response\n");
		}
		sleep(1);
	}
	free(req);
	free(data);
	server_close(srv);
	
	return 0;
}
