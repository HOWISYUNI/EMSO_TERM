#include <stdio.h>

/*커맨드 라이브러리*/
#include "../lib/abnormal_situation_lib.h"
#include "../lib/unidentifid_object_lib.h"
#include "../lib/led_lib.h"
#include "../lib/sprinkler_lib.h"
/*네트워크 라이브러리*/
#include "../lib/SF_NET/ksf_client.lib.h"

int main(){

	struct response rcv;

	/*클라이언트 초기화*/
	client_init(src_ip, dest_ip, port, type);

	/*r3에 일정주기마다 데이터 요청*/
	while(1){
		/*일정주기마다 요청하기위해 delay를 줌*/
		delay(1000);
		/*r3에 온습도 데이터를 요청함.*/
		rcv = request_get(socket, type, data, cmd);
		sig = check_sprinkler();	/*rcv값에 따라서 스프링클러 작동여부 구하는 함수*/
		if(sig){
			send_sprinkler_siganl();	/*작동하기로 했으면 시그널을 보냄*/
		}
		/*r3에 조도 데이터를 요청함*/
		rcv = request_get();
		sig = check_led();	/*rcv값에 따라서 led 작동여부 구하는 함수*/
		if(sig){
			send_led_signal();	/*작동하기로 했으면 시그널을 보냄*/
		}
	
	}

	return 0;
}
