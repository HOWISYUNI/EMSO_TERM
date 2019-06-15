#include "./user_interface.h"

int main(){
	
	int input;

	char rcv_str[BUF];
	int soil_a;
	int light_a;
	
	char c;
	//char ss[1024] = "aaaa\nbbbb\ncccc\ndddd\n";
	//char c;
	//parse(ss);
	//scanf("%c", &c);
	while(1){
		system("clear");
		printf("-----------------------------------------\n");
		printf("* 1. r1의 스프링클러 켜기               *\n");
		printf("* 2. r1의 led 켜기                      *\n");
		printf("* 3. r3에 토양온습도 최근 n개 요청      *\n");
		printf("* 4. r3에 조도 최근 n개 요청            *\n");
		printf("* 5. r3에 토양온습도 평균값 요청        *\n");
		printf("* 6. r3에 조도 평균값 요청              *\n");
		printf("* 0. 종료                               *\n");
		printf("-----------------------------------------\n");
		printf("토양온습도 평균값:%d  조도 평균값:%d     \n\n", soil_a, light_a);
		scanf("%d", &input);

		if(input == 1){
			int socket_r1 = client_open(R1_ADDR, R1_ACT_PORT, 5);

			client_close(socket_r1);			
		}else if(input == 2){
			int socket_r1 = client_open(R1_ADDR, R1_ACT_PORT, 5);

			client_close(socket_r1);
		}else if(input == 3){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			request_soil_recent_to_r3(socket_r3, rcv_str);
			client_close(socket_r3);
			printf("--최근 토양온습도 값들--\n");
			parse(rcv_str);
			scanf("%c", &c);
		}else if(input == 4){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			request_light_recent_to_r3(socket_r3, rcv_str);
			client_close(socket_r3);
			printf("--최근 조도 값들--\n");
			parse(rcv_str);
			scanf("%c", &c);
		}else if(input == 5){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			soil_a = request_soil_average_to_r3(socket_r3);
			client_close(socket_r3);
			printf("토양온습도 평균값: %d\n", soil_a);
			scanf("%c", &c);
		}else if(input == 6){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			light_a = request_light_average_to_r3(socket_r3);
			client_close(socket_r3);
			printf("조도 평균값: %d\n", light_a);
			scanf("%c", &c);
		}else if(input == 0){
			printf("종료합니다.\n");
			scanf("%c", &c);
			break;
		}else{

		}

	}


	return 0;
}

/*3번*/
void request_soil_recent_to_r3(int socket, char* str){
	struct response rcv;
	char rcv_data[BUF];
	rcv = request(socket, 'G', 's', 'r', 1, "5");
	//rcv_data = rcv.data;
	strcpy(str, rcv.data);
}

/*4번*/
void request_light_recent_to_r3(int socket, char* str){
	struct response rcv;
	char rcv_data[BUF];
	rcv = request(socket, 'G', 'l', 'r', 1, "5");
	strcpy(str, rcv.data);

}

/*5번*/
int request_soil_average_to_r3(int socket){
	struct response rcv;
	int rcv_data;
	rcv = request(socket, 'G', 's', 'a', 2, "10");
	rcv_data = (int)rcv.data;
	
	return rcv_data;
}

/*6번*/
int request_light_average_to_r3(int socket){
	struct response rcv;
	int rcv_data;
	rcv = request(socket, 'G', 'l', 'a', 2, "10");
	rcv_data = (int)rcv.data;	

	return 0;
}

/*recent값으로 여러개를 받아오면 구분자로 파싱해서 보여주는 함수*/
void parse(char* str){
	char delimeter[10] = ",\n";
	char *pch;

	pch = strtok(str, delimeter);
	while(pch){
		printf("%s\n", pch);
		pch = strtok(NULL, delimeter);
	}

}
