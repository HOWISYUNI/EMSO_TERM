#include <stdio.h>

#include "../lib/SF_NET/ksf_server_lib.h"

int main(){
	struct response rcv;
	struct request req;
	int sock, c_sock;
	
	while(1){
		sock = server_open(R3_STG_PORT);

		c_sock = wait_request(sock, req);		/* 데이터 수신 대기 */
		
		/* cmd is save('s') */
		if(req.cmd == 's'){		//method??
			save_data(req.type, req.data);

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
			ret = response(c_sock, 's', 0, '\n');
		}
		else{
			ret = response(c_sock, 'f', 0 , "Failed not save");
		}

		//delay(1000);
		
		server_close(sock);
	}
	return 0;
}
