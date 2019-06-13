#include "./data_controller.h"

/*R1으로부터 받는 데이터를 처리*/
int main(void){

	int socket_r1;
	int socket_r3;

	struct request rcv;

	/*소켓 초기화*/
	socket_r1 = server_open(R2_DATA_PORT);
	socket_r3 = client_open(R3_ADDR, R3_STG_PORT);

	/*요청 대기*/
	while(1){
		wait_request(socket_r1, &rcv);

		if(rcv.type == 's'){	/*온습도 데이터*/
			/*r3에게 데이터 전송*/
			send_humidity_data_to_r3(socket_r3, rcv);
		}else if(rcv.type == 'l'){	/*조도 데이터*/
			/*r3에게 데이터 전송*/
			send_light_data_to_r3(socket_r3, rcv);
		}else if(rcv.type == 'a'){	/*비정상 상황 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			send_abnormal_situation_to_r3(socket_r3, rcv);
		}else if(rcv.type == 'a'){	/*미확인 물체 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			send_unidentified_object_to_r3(socket_r3, rcv);
		}else{	/**/

		}
	
	}

	server_close(socket_r1);

	return 0;
}

/*비정상 상황 r3에 전송*/
void send_abnormal_situation_to_r3(int socket, struct request data_r1){

	struct response rcv;

	rcv = request(socket, 'O', 'a', 's', data_r1.len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

}

/*r3에 토양 온습도데이터 전달*/
void send_humidity_data_to_r3(int socket, struct request data_r1){

	struct response rcv;

	rcv = request(socket, 'O', 's', 's', data_r1.len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

}

/*r3에 빛 데이터 전송*/
void send_light_data_to_r3(int socket, struct request data_r1){
	struct response rcv;

	rcv = request(socket, 'O', 'l', 's', data_r1.len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

}

/*r3에 미확인 물체 데이터 전송*/
void send_unidentified_object_to_r3(int socket, struct request data_r1){
	struct response rcv;

	rcv = request(socket, 'O', 'a', 's', data_r1.len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

}

/*비정상 상황시 알람 메시지*/
int alert_situation(){
	/*비정상 상황 발생시 부저 울림*/
	printf("알람알람알람");
	return 0;
}


