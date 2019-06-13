#include "./command_controller.h"

int main(){

	struct response rcv;
	int sig;	/*actuator 작동여부*/
	int socket_r1, socket_r3;

	/*클라이언트 초기화*/
	socket_r1 = client_open(R1_ADDR, R1_ACT_PORT);
	socket_r3 = client_open(R3_ADDR, R3_REF_PORT);

	/*r3에 일정주기마다 데이터 요청*/
	while(1){
		/*일정주기마다 요청하기위해 delay를 줌*/
		sleep(1000);

		/*r3에 토양 온습도 데이터를 요청함.*/
		rcv = request(socket_r3, 'G', 's', 'v', 0, "");
		sig = check_sprinkler((int)rcv.data);	/*rcv값에 따라서 스프링클러 작동여부 구하는 함수*/		
		send_sprinkler_signal(socket_r3, sig);	/*작동하기로 했으면 시그널을 보냄*/

		/*r3에 조도 데이터를 요청함*/
		rcv = request(socket_r1, 'G', 'l', 'v', 0, "");
		sig = check_led((int)rcv.data);	/*rcv값에 따라서 led 작동여부 구하는 함수*/
		send_led_signal(socket_r1, sig);	/*작동하기로 했으면 시그널을 보냄*/
		
	
	}

	return 0;
}

void send_sprinkler_signal(int socket, int sig){
	if(sig == true){
		request(socket, 'U', 's', '1', 0, "true");
	}else{
		/*보낼필요없음*/
	}

}

void send_led_signal(int socket, int sig){
	if(sig == true){
		request(socket, 'U', 'l', '1', 0, "true");
	}else{
		/*보낼필요없음*/
	}

}
