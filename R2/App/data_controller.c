#include "./data_controller.h"

/*R1으로부터 받는 데이터를 처리*/
int main(void){

	int socket_r1;
	int socket_r3;
	
	int c_socket;
	int ret;
	
	struct request rcv;
	struct response res;
	/*소켓 초기화*/
	socket_r1 = server_open(R2_DATA_PORT);
	
	/*요청 대기*/
	while(1){
		printf("wait_request\n");
		c_socket = wait_request(socket_r1, &rcv);
		printf("받은 값 : %d\n", atoi(rcv.data));
		//printf("0\n");
		strcpy(res.data,"\n");
		if(response(c_socket, SUCCESS, 0, res.data) < 0 ){
			/*ERROR*/
			printf("response error");
		}
		printf("r3에게 보내기위한 소켓 OPEN\n");
		socket_r3 = client_open(R3_ADDR, R3_STG_PORT,WAIT_RSP);
		
		if(rcv.type == SOIL){	/*온습도 데이터*/
			/*r3에게 데이터 전송*/
			printf("온습도데이터 전송\n");
			send_humidity_data_to_r3(socket_r3, rcv);
		}else if(rcv.type == LIGHT){	/*조도 데이터*/
			/*r3에게 데이터 전송*/
			printf("조도데이터 전송\n");
			send_light_data_to_r3(socket_r3, rcv);
		}else if(rcv.type == EMG_T){	/*비정상 상황 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			printf("비정상 상황 신호 전송\n");
			send_abnormal_situation_to_r3(socket_r3, rcv);
		}else if(rcv.type == EMG_P){	/*미확인 물체 신호*/
			/*r3에게 데이터 전송 및 알람 메시지*/
			printf("미확인 물체 신호 전송\n");
			send_unidentified_object_to_r3(socket_r3, rcv);
		}else{	/**/

		}
		printf("r3에게 보내기위한 소켓 CLOSE\n");
		client_close(socket_r3);
	}

	printf("server close\n");
	server_close(socket_r1);

	return 0;
}

/*비정상 상황 r3에 전송*/
void send_abnormal_situation_to_r3(int socket, struct request data_r1){

	struct response rcv;

	int len = strlen(data_r1.data);
	rcv = request(socket, POST, EMG_T, STORE, len, data_r1.data);
	scp_snapshot(rcv.data);
	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.type == FAILURE){
        printf("send_abnormal_situation_to_r3 - Fail\n");
    }else if(rcv.type == TIME_OUT){
        printf("send_abnormal_situation_to_r3 - Timeout\n");
    }

}

/*r3에 토양 온습도데이터 전달*/
void send_humidity_data_to_r3(int socket, struct request data_r1){

	struct response rcv;

	int len = strlen(data_r1.data);
	rcv = request(socket, POST, SOIL, STORE, len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.type == FAILURE){
        printf("send_humidity_data_to_r3 - Fail\n");
    }else if(rcv.type == TIME_OUT){
        printf("send_humidity_data_to_r3 - Timeout\n");
    }

}

/*r3에 빛 데이터 전송*/
void send_light_data_to_r3(int socket, struct request data_r1){
	struct response rcv;

    int len = strlen(data_r1.data);
	rcv = request(socket, POST, LIGHT, STORE, len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.type == FAILURE){
        printf("send_light_data_to_r3 - Fail\n");
    }else if(rcv.type == TIME_OUT){
        printf("send_light_data_to_r3 - Timeout\n");
    }

}

/*r3에 미확인 물체 데이터 전송*/
void send_unidentified_object_to_r3(int socket, struct request data_r1){
	struct response rcv;

	int len = strlen(data_r1.data);
	rcv = request(socket, POST, EMG_P, STORE, len, data_r1.data);
    scp_snapshot(rcv.data);
	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.type == FAILURE){
		printf("send_unidentified_object_to_r3 - Fail\n");
	}else if(rcv.type == TIME_OUT){
		printf("send_unidentified_object_to_r3 - Timeout\n");
	}

}

/*비정상 상황시 알람 메시지*/
int alert_situation(){
	/*비정상 상황 발생시 부저 울림*/
	printf("알람알람알람");
	return 0;
}

/* camera snapshot */
int scp_snapshot(char *file_name){
    char *ptr;
    pid_t pid;
    pid = fork();
    
    if(pid < 0){
        /* fail to fork */
        printf("fail to fork\n");
        return -1;
    }
    else if(pid == 0){
        ptr = strtok(file_name, " ");
        /* child process */
        execl("/bin/sh", "sh", "./copy_from_r4.sh", ptr, NULL);
    }
    else{
    
        return pid;
    }
}

