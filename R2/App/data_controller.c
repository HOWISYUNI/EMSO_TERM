#include <stdio.h>
#include <stdlib.h>

/**/
#include "../lib/lib/abnormal_situation_lib.h"
#include "" 
#include ""
#include ""

/*네트워크 라이브러리*/
#include "../lib/SF_NET/ksf_server_lib.h"
#include "../lib/SF_NET/ksf_client-lib.h"

/*R1으로부터 받는 데이터를 처리*/
int main(void){

	struct request rcv;
	int socket;

	/*서버 초기화*/
	socket = server_init(ip, port);

	/*요청 대기*/
	while(1){
		rcv = wait_request(socket);

		if(rcv.type == ""){	/*토양 온습도 데이터*/
			/*r3에게 데이터 전송*/
			send_humidity_data_to_r3(socket);
		}else if(rcv.type == ""){	/*조도 데이터*/
			/*r3에게 데이터 전송*/
			send_light_data_to_r3(socket);
		}else if(){	/*비정상 상황 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			send_abnormal_situation_to_r3(socket);
		}else if(){	/*미확인 물체 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			send_unidentified_object_to_r3(socket);
		}else{	/**/

		}
	
	}

	return 0;
}
