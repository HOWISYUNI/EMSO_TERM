#include <stdio.h>
#include <unistd.h>

#include "../../KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(){
	int sock, c_sock, ret, data;
	
	struct request *req;

	req = (struct request*)malloc(sizeof(struct request));
	sock = server_open(R3_STG_PORT);
	printf("R3.storage_controller init\n");
	
	while(1){
		printf("wait request from R2.data_controller\n");		
		c_sock = wait_request(sock, req);
		
		data = atoi(req->data);
		if(data == 0){
			printf("Data is 0!! No save!!\n");
			sleep(1);
			continue;
		}

		/* cmd is save('s') */
		if(req->cmd == STORE){
			ret = save_data(req->type, req->data);
			if(ret < 0){
				printf("Failed save_data function!!\n");
				ret = response(c_sock, FAILURE, sizeof("Failed not save_data func"), "Failed not save_data func");
			}
			else{
				printf("Successed saving data!!\n");
				ret = response(c_sock, SUCCESS, sizeof("Successed saving data"), "Successed saving data");
			}
		}
		else{
    		/* not support request cmd */
			printf("not support request command\n");
			ret = response(c_sock, FAILURE, sizeof("not support request"), "not support request");
		}
		/* response failed */
		if(ret < 0){
		    printf("failed send response\n");
		}
		sleep(1);
	}
	free(req);
	server_close(sock);
	
	return 0;
}
