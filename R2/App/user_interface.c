#include "./user_interface.h"

char rcv_str[BUF];

int main(){
	
	int input;

	struct response rcv;
	
	int soil_a;
	int light_a;
	
	int c;
	
	while(1){
		system("clear");
		printf("------------------------------------------\n");
		printf("* 1. r1의 스프링클러 켜기    11. 끄기      *\n");
		printf("* 2. r1의    led     켜기    22. 끄기     *\n");
		printf("* 3. r1의 카메라 촬영                     *\n");
		printf("* 4. r1의    버저   울리기   44. 끄기      *\n");
		printf("* 5. r3에 토양온습도 최근 n개 요청          *\n");
		printf("* 6. r3에 조도 최근 n개 요청               *\n");
		printf("* 7. r3에 토양온습도 평균값 요청            *\n");
		printf("* 8. r3에 조도 평균값 요청                 *\n");
		printf("* 9. r3에 토양온습도 값 전달               *\n");
		printf("* 10. r3에 조도 값 전달                   *\n");
		printf("* 11. r1에 alert 신호 보내기              *\n");
		printf("* 0. 종료                                *\n");
		printf("------------------------------------------\n");
		printf("******************************************\n");
		printf("토양온습도 평균값:%d  조도 평균값:%d      \n", soil_a, light_a);
		printf("******************************************\n");
		//printf("--토양온습도, 조도 최근값--\n");
		printf("%s\n", rcv_str);
		//parse(rcv_str);
		printf("******************************************\n");
		printf("선택해라.\n");
		scanf("%d", &input);

		if(input == 1){
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);		
			send_sprinkler_signal(socket_r1, true);
			client_close(socket_r1);			
		}else if(input == 2){
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			send_led_signal(socket_r1, true);
			client_close(socket_r1);
		}else if(input == 11){
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			send_sprinkler_signal(socket_r1, false);
			client_close(socket_r1);
		}else if(input == 22){
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			send_led_signal(socket_r1, false);
			client_close(socket_r1);
		}else if(input == 3){//카메라
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			
			rcv = request(socket_r1, 'U', 'c', '1', 0, "true");
			if(rcv.type == 'f'){
				printf("send_camera_siganl - Fail\n");
				strcpy(rcv_str, "send_camera_signal - Fail\n");
				sleep(3);
			}else if(rcv.type == 't'){
				printf("send_camera_signal - Timeout\n");
				strcpy(rcv_str, "send_camera_signal - Timeout\n");
				sleep(3);
			}
			
			client_close(socket_r1);
		}else if(input == 4){//버저 울기
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			
			rcv = request(socket_r1, 'U', 'b', '1', 0, "true");
			if(rcv.type == 'f'){
				printf("send_buzzer_siganl - Fail\n");
				strcpy(rcv_str, "sned_buzzer_signal - Fail\n");
				sleep(3);
			}else if(rcv.type == 't'){
				printf("send_buzzer_signal - Timeout\n");
				strcpy(rcv_str, "sned_buzzer_signal - Timeout\n");
				sleep(3);
			}
			
			client_close(socket_r1);
		}else if(input == 44){//버저 끄기
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			
			rcv = request(socket_r1, 'U', 'b', '0', 0, "false");
			if(rcv.type == 'f'){
				printf("send_buzzer_siganl - Fail\n");
				strcpy(rcv_str, "sned_buzzer_signal - Fail\n");
				sleep(3);
			}else if(rcv.type == 't'){
				printf("send_buzzer_signal - Timeout\n");
				strcpy(rcv_str, "sned_buzzer_signal - Timeout\n");
				sleep(3);
			}
			
			client_close(socket_r1);
		}else if(input == 5){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			request_soil_recent_to_r3(socket_r3, rcv_str);
			client_close(socket_r3);
			//printf("--최근 토양온습도 값들--\n");
			//parse(rcv_str);
			//fflush(stdin);
			//printf("넘어가려면 아무거나 누르세요.");
			//getchar();
			//scanf("%d", &c);
			//sleep(5);
		}else if(input == 6){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			request_light_recent_to_r3(socket_r3, rcv_str);
			client_close(socket_r3);
			//printf("--최근 조도 값들--\n");
			//parse(rcv_str);
			//fflush(stdin);
			//printf("넘어가려면 아무거나 누르세요.");
			//getchar();
			//scanf("%d", &c);
			//sleep(5);
		}else if(input == 7){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			soil_a = request_soil_average_to_r3(socket_r3);
			client_close(socket_r3);
			//printf("토양온습도 평균값: %d", soil_a);
			//fflush(stdin);
			//printf("넘어가려면 아무거나 누르세요.");
			//getchar();
			//scanf("%d", &c);
		}else if(input == 8){
			int socket_r3 = client_open(R3_ADDR, R3_REF_PORT, 5);
			light_a = request_light_average_to_r3(socket_r3);
			client_close(socket_r3);
			//printf("조도 평균값: %d\n", light_a);
			//fflush(stdin);
			//printf("넘어가려면 아무거나 누르세요.");
			//getchar();
			//scanf("%d", &c);
		}else if(input == 9){/*r3에 토양온습도 값 전달*/
			char data[BUF];
			//fflush(stdin);
			scanf("%s", data);
			int socket_r3 = client_open(R3_ADDR, R3_STG_PORT, 5);
			rcv = request(socket_r3, 'O', 's', 's', strlen(data), data);
			client_close(socket_r3);
		}else if(input == 10){/*r3에 조도 값 전달*/
			char data[BUF];
			//fflush(stdin);
            scanf("%s", data);
            int socket_r3 = client_open(R3_ADDR, R3_STG_PORT, 5);
            rcv = request(socket_r3, 'O', 'l', 's', strlen(data), data);
            client_close(socket_r3);
		}else if(input == 11){
			int socket_r1 = client_open(R4_ADDR, R4_ACT_PORT, 5);
			
			rcv = request(socket_r1, 'U', 'a', '1', 0, "true");
			if(rcv.type == 'f'){
				printf("send_alert_siganl - Fail\n");
				strcpy(rcv_str, "sned_alert_signal - Fail\n");
				sleep(3);
			}else if(rcv.type == 't'){
				printf("send_buzzer_signal - Timeout\n");
				strcpy(rcv_str, "sned_alert_signal - Timeout\n");
				sleep(3);
			}
			
			client_close(socket_r1);
		}else if(input == 0){
			printf("종료합니다.\n");
			//fflush(stdin);
			//scanf("%d", &c);
			break;
		}else{

		}

	}


	return 0;
}

/*1번, 11번*/
void send_sprinkler_signal(int socket, int sig){
    struct response rcv;
    if(sig == true){
        rcv = request(socket, 'U', 's', '1', 0, "true");
        if(rcv.type == 'f'){
		printf("send_sprinkler_siganl - Fail\n");
		strcpy(rcv_str, "sned_sprinkler_signal - Fail\n");
		sleep(3);
        }else if(rcv.type == 't'){
		printf("send_sprinkler_signal - Timeout\n");
		strcpy(rcv_str, "sned_sprinkler_signal - Timeout\n");
		sleep(3);
        }

    }else{
        rcv = request(socket, 'U', 's', '0', 0, "false");
        if(rcv.type == 'f'){
            printf("send_sprinkler_siganl - Fail\n");
		strcpy(rcv_str, "sned_sprinkler_signal - Fail\n");
            sleep(3);
        }else if(rcv.type == 't'){
            printf("send_sprinkler_signal - Timeout\n");
		strcpy(rcv_str, "sned_sprinkler_signal - Timeout\n");
            sleep(3);
        }

    }

}

/*2번, 22번*/
void send_led_signal(int socket, int sig){
    struct response rcv;
    if(sig == true){
        request(socket, 'U', 'l', '1', 0, "true");
        if(rcv.type == 'f'){
            printf("send_led_signal - Fail\n");
		strcpy(rcv_str, "sned_led_signal - Fail\n");
			sleep(3);
        }else if(rcv.type == 't'){
            printf("send_len_signal - Timeout\n");
		strcpy(rcv_str, "sned_led_signal - Timeout\n");
			sleep(3);
        }

    }else{
        request(socket, 'U', 'l', '0', 0, "false");
        if(rcv.type == 'f'){
            printf("send_led_signal - Fail\n");
		strcpy(rcv_str, "sned_led_signal - Fail\n");
            sleep(3);
        }else if(rcv.type == 't'){
            printf("send_len_signal - Timeout\n");
		strcpy(rcv_str, "sned_led_signal - Timeout\n");
            sleep(3);
        }

    }

}

/*5번*/
void request_soil_recent_to_r3(int socket, char* str){
	struct response rcv;
	//char rcv_data[BUF];
	rcv = request(socket, 'G', 's', 'v', 1, "5");
	//rcv_data = rcv.data;
	strcpy(str, rcv.data);
}

/*6번*/
void request_light_recent_to_r3(int socket, char* str){
	struct response rcv;
	//char rcv_data[BUF];
	rcv = request(socket, 'G', 'l', 'v', 1, "5");
	strcpy(str, rcv.data);

}

/*7번*/
int request_soil_average_to_r3(int socket){
	struct response rcv;
	int rcv_data;
	rcv = request(socket, 'G', 's', 'a', 2, "10");
	rcv_data = atoi(rcv.data);
	
	return rcv_data;
}

/*8번*/
int request_light_average_to_r3(int socket){
	struct response rcv;
	int rcv_data;
	rcv = request(socket, 'G', 'l', 'a', 2, "10");
	rcv_data = atoi(rcv.data);

	return rcv_data;
}

/*recent값으로 여러개를 받아오면 구분자로 파싱해서 보여주는 함수*/
void parse(char* str){
	char delimeter[10] = "\n";
	char *pch;

	pch = strtok(str, delimeter);
	while(pch){
		printf("%s\n", pch);
		pch = strtok(NULL, delimeter);
	}

}

void recent_print(char* str){

	printf("%s\n", str);

}
