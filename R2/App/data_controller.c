#include <stdio.h>터
#include <stdlib.h>
#include "../lib/SF_NET/ksf_server_lib.h"
#include "../lib/SF_NET/ksf_client-lib.h"

/*R1으로부터 받는 데이터를 처리*/
int main(void){

	struct request rcv;

	/*서버 초기화*/
	server_init(ip, port);

	/*요청 대기*/
	while(1){
		rcv = wait_request(socket);

		if(rcv.type == ""){	/*온습도 데이터*/
			/*r3에게 데이터 전송*/
		}else if(rcv.type == ""){	/*조도 데이터*/
			/*r3에게 데이터 전송*/
		}else if(){	/*비정상 상황 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
		}else if(){	/*미확인 물체 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
		}else{	/**/

		}
	
	}

	return 0;
}
