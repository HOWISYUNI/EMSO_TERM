#include <stdio.h>
#include <unistd.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(){
	int sock, c_sock, ret;
	char *suc = "success";	//To send "success" message in response func
	
	struct request *req;

	req = (struct request*)malloc(sizeof(struct request));
	sock = server_open(R3_STG_PORT);
	while(1){
		printf("Wait!!\n");		
		c_sock = wait_request(sock, req);		/* 데이터 수신 대기 */
		
		/* cmd is save('s') */
		if(req->cmd == 's'){		//method??
			ret = save_data(req->type, req->data);
			if(ret < 0){
				ret = response(c_sock, 'f', 0, "Failed not save_data func");
			}
			else{
				ret = response(c_sock, 's', 0, suc);
			}
		}
		else{
			ret = response(c_sock, 'f', 0 , "cmd data is strange");
		}
		sleep(3);
	}
	free(req);
	server_close(sock);
	
	return 0;
}
