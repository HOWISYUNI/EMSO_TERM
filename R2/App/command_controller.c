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
	    socket_r3 = client_open(R3_ADDR, R3_REF_PORT, WAIT_RSP);
		
		/*r3에 토양 온습도 데이터를 요청함.*/
		printf("r3에 request\n");
		rcv = request(socket_r3, GET, SOIL, AVERAGE, 2, "10");

		printf("r3에 연결된 소켓 CLOSE\n");
		client_close(socket_r3);

		/*rcv값에 따라서 스프링클러 작동여부 구하는 함수*/
		printf("작동여부 구함.\n");
		sig = check_sprinkler(atoi(rcv.data));

		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		printf("r1에 소켓 OPEN\n");
		socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, WAIT_RSP);
		if(rcv.type == FAILURE){
			printf("토양온습도 fail\n");
    	}else if(rcv.type == TIME_OUT){
			printf("토양온습도 timeout\n");
	    }
	    
		send_sprinkler_signal(socket_r1, sig);	/*작동하기로 했으면 시그널을 보냄*/
        
		printf("r1에 연결된 소켓 CLOSE\n");
		client_close(socket_r1);


		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		printf("r3에 소켓 OPEN\n");
	    socket_r3 = client_open(R3_ADDR, R3_REF_PORT, WAIT_RSP);

		/*r3에 조도 데이터를 요청함*/
		printf("r3에 request\n");
		rcv = request(socket_r3, GET, LIGHT, AVERAGE, 2, "10");

		printf("r3에 연결된 소켓 CLOSE\n");
		client_close(socket_r3);
	
		/*rcv값에 따라서 led 작동여부 구하는 함수*/
		printf("작동여부 구함.\n");
		sig = check_led(atoi(rcv.data));

		/*클라이언트 초기화 및 시그널 전송---------------------------------------*/
		printf("r1에 소켓 OPEN\n");
		socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, WAIT_RSP);
		if(rcv.type == FAILURE){
			printf("조도 fail\n");
   		}else if(rcv.type == TIME_OUT){
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
	if(sig == true){/*스프링클러 켜는 신호 전송*/
		rcv = request(socket, PUT, SPRINKLER, TURN_ON, 0, "turn on sprinkler");
		if(rcv.type == FAILURE){
			printf("send_sprinkler_siganl - Fail\n");
		}else if(rcv.type == TIME_OUT){
        	printf("send_sprinkler_signal - Timeout\n");
		}

	}else{/*스프링클러 끄는 신호 전송*/
		rcv = request(socket, PUT, SPRINKLER, TURN_OFF, 0, "turn off sprinkler");
    	if(rcv.type == FAILURE){
    	    printf("send_sprinkler_siganl - Fail\n");
    	}else if(rcv.type == TIME_OUT){
	        printf("send_sprinkler_signal - Timeout\n");
    	}

	}

}

void send_led_signal(int socket, int sig){
	struct response rcv;
	if(sig == true){
		request(socket, PUT, LED, TURN_ON, 0, "turn on led");
		if(rcv.type == FAILURE){
	        	printf("send_led_signal - Fail\n");
		}else if(rcv.type == TIME_OUT){
			printf("send_len_signal - Timeout\n");
		}

	}else{
		request(socket, PUT, LED, TURN_OFF, 0, "turn off led");
        	if(rcv.type == FAILURE){
			printf("send_led_signal - Fail\n");
        	}else if(rcv.type == TIME_OUT){
        	    printf("send_len_signal - Timeout\n");
        	}


	}

}
