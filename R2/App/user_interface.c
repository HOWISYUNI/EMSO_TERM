#include "./user_interface.h"

int main(){
	
	int input;

	struct request rcv;

	int socket_r1 = client_open(dest_ip, port);
	int socket_r3 = client_open(dest_ip, port);

	while(1){
		system("clear");
		printf("-----------------------------------------\n");
		printf("* 1. r1의 스프링클러 켜기                    *\n");
		printf("* 2. r1의 led 켜기                           *\n");
		printf("* 3. r3에 토양온습도 평균값 요청        *\n");
		printf("* 4. r3에 조도 평균값 요청              *\n");
		printf("-----------------------------------------\n");
		scanf("%d", &input);

		if(input == 1){
			
		}else if(input == 2){
			
		}else if(input == 3){
			
		}else if(input == 4){

		}else{

		}

	}


	return 0;
}

/*3번*/
int request_humidity_to_r3(int socket){
	
	

	return 0;
}

/*4번*/
int request_light_to_r3(int socket){

	

	return 0;
}
