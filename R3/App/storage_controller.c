#include <stdio.h>

#include "../lib/KSF_NET/ksf_net_lib.h"
#include "../lib/controllers.h"

int main(){
	struct request req;
	int sock, c_sock, ret;
	char *suc = "success";
	
	while(1){
		sock = server_open(3010);
		c_sock = wait_request(sock, &req);		/* 데이터 수신 대기 */
		
		/* cmd is save('s') */
		if(req.cmd == 's'){		//method??
			ret = save_data(req.type, req.data);
			if(ret < 0){
				ret = response(c_sock, 'f', 0 , "Failed not save_data func");
			}
			/*
			if(req.type == 'l'){
				save_light(req.len, req.data);
			}
			else if(req.type == 's'){
				save_soil(req.len, req.data);
			}
			else if(req.type == 'a'){
				save_data
			}
			*/
			ret = response(c_sock, 's', 0, suc);
		}
		else{
			ret = response(c_sock, 'f', 0 , "Failed not save");
		}

		//delay(1000);
		
		server_close(sock);
	}
	return 0;
}
