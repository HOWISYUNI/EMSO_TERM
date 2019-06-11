#include "./data_controller.h"

/*R1으로부터 받는 데이터를 처리*/
int main(void){

	struct request rcv;

	/*소켓 초기화*/
	socket_r1 = server_open(port);
	socket_r3 = client_open(dest_ip, port)


	/*요청 대기*/
	while(1){
		rcv = wait_request(socket_r1);

		if(rcv.type == ""){	/*온습도 데이터*/
			/*r3에게 데이터 전송*/
			send_humidity_data_to_r3(socket_r3);
		}else if(rcv.type == ""){	/*조도 데이터*/
			/*r3에게 데이터 전송*/
			send_light_data_to_r3(socket_r3);
		}else if(){	/*비정상 상황 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			send_abnormal_situation_to_r3(socket_r3);
		}else if(){	/*미확인 물체 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			send_unidentified_object_to_r3(socket_r3);
		}else{	/**/

		}
	
	}

	server_close(socket_r1);

	return 0;
}
