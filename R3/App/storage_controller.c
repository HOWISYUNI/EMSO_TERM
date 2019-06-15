#include <stdio.h>
#include <unistd.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(){
	int sock, c_sock, ret;
	
	struct request *req;

	req = (struct request*)malloc(sizeof(struct request));
	sock = server_open(R3_STG_PORT);
	while(1){
		printf("Wait for saving data!!\n");		
		c_sock = wait_request(sock, req);		/* 데이터 수신 대기 */
		
		/* cmd is save('s') */
		if(req->cmd == 's'){		//method??
			ret = save_data(req->type, req->data);
			if(ret < 0){
				printf("Failed save_data function!!\n");
				ret = response(c_sock, 'f', 0, "Failed not save_data func");
			}
			else{
				printf("Successed saving data!!\n");
				ret = response(c_sock, 's', 0, "Successed saving data");
			}
		}
		else{
			printf("Cmd data is strange!!\n");
			ret = response(c_sock, 'f', 0 , "cmd data is strange");
		}
		sleep(1);
	}
	free(req);
	server_close(sock);
	
	return 0;
}
