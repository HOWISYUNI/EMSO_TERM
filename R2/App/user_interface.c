#include "./user_interface.h"

int main(){
	
	int input;

	struct request rcv;

	//int socket_r1 = client_open(R1_ADDR, R1_ACT_PORT);
	//int socket_r3 = client_open(R3_ADDR, R3_REF_PORT);
	int socket_r3 = client_open("127.0.0.1", 4000);


	int soil = 0;
	int light = 0;

	while(1){
		system("clear");
		printf("-----------------------------------------\n");
		printf("* 1. r1의 스프링클러 켜기                    *\n");
		printf("* 2. r1의 led 켜기                           *\n");
		printf("* 3. r3에 토양온습도 평균값 요청        *\n");
		printf("* 4. r3에 조도 평균값 요청              *\n");
		printf("-----------------------------------------\n");
		printf("토양온습도 평균값:%d  조도 평균값:%d     \n\n", soil, light);
		scanf("%d", &input);

		if(input == 1){
			
		}else if(input == 2){
			
		}else if(input == 3){
			soil = request_humidity_to_r3(socket_r3);
		}else if(input == 4){
			light = request_light_to_r3(socket_r3);
		}else{

		}

	}


	return 0;
}

/*3번*/
int request_humidity_to_r3(int socket){
	struct response rcv;
	int rcv_data;
	rcv = request(socket, 'G', 's', 'a', 0, "");
	rcv_data = (int)rcv.data;
	
	return rcv_data;
}

/*4번*/
int request_light_to_r3(int socket){
	struct response rcv;
	int rcv_data;
	rcv = request(socket, 'G', 'l', 'a', 0, "");
	rcv_data = (int)rcv.data;	

	return 0;
}
