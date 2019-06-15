#include "./command_controller.h"

int main(){

	struct response rcv;
	int sig;	/*actuator 작동여부*/
	int socket_r1, socket_r3;

	/*r3에 일정주기마다 데이터 요청*/
	while(1){
		/*일정주기마다 요청하기위해 delay를 줌*/
		sleep(2);

		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		printf("r3에 소켓 OPEN\n");
	    	socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 10);
		
		/*r3에 토양 온습도 데이터를 요청함.*/
		printf("r3에 request\n");
		rcv = request(socket_r3, 'G', 's', 'a', 2, "10");

		printf("r3에 연결된 소켓 CLOSE\n");
		client_close(socket_r3);

		/*rcv값에 따라서 스프링클러 작동여부 구하는 함수*/
		printf("작동여부 구함.\n");
		sig = check_sprinkler((int)rcv.data);

		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		printf("r1에 소켓 OPEN\n");
		socket_r1 = client_open(R1_ADDR, R1_ACT_PORT, 10);
		if(rcv.type == 'f'){
			printf("토양온습도 fail\n");
    		}else if(rcv.type == 't'){
			printf("토양온습도 timeout\n");
	    	}
		send_sprinkler_signal(socket_r1, sig);	/*작동하기로 했으면 시그널을 보냄*/
        
		printf("r1에 연결된 소켓 CLOSE\n");
		client_close(socket_r1);


		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		printf("r3에 소켓 OPEN\n");
	    	socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 10);

		/*r3에 조도 데이터를 요청함*/
		printf("r3에 request\n");
		rcv = request(socket_r3, 'G', 'l', 'a', 2, "10");

		printf("r3에 연결된 소켓 CLOSE\n");
		client_close(socket_r3);
	
		/*rcv값에 따라서 led 작동여부 구하는 함수*/
		printf("작동여부 구함.\n");
		sig = check_led((int)rcv.data);

		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		socket_r1 = client_open(R1_ADDR, R1_ACT_PORT, 10);
		if(rcv.type == 'f'){
			printf("조도 fail\n");
   		}else if(rcv.type == 't'){
			printf("조도 fail\n");
    		}
		send_led_signal(socket_r1, sig);	/*작동하기로 했으면 시그널을 보냄*/
		
		printf("r1에 연결된 소켓 CLOSE\n");
		client_close(socket_r1);	

	}

	return 0;
}

void send_sprinkler_signal(int socket, int sig){
	struct response rcv;
	if(sig == true){
		rcv = request(socket, 'U', 's', '1', 0, "true");
		if(rcv.type == 'f'){
			printf("send_sprinkler_siganl - Fail\n");
		}else if(rcv.type == 't'){
	        	printf("send_sprinkler_signal - Timeout\n");
		}

	}else{
		/*보낼필요없음*/
	}

}

void send_led_signal(int socket, int sig){
	struct response rcv;
	if(sig == true){
		printf("r1");
		request(socket, 'U', 'l', '1', 0, "true");
		if(rcv.type == 'f'){
	        	printf("send_led_signal - Fail\n");
		}else if(rcv.type == 't'){
			printf("send_len_signal - Timeout\n");
		}

	}else{
		/*보낼필요없음*/
	}

}
