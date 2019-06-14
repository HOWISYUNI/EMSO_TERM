#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "app.h"



int send_light_data_to_r2(int socket);
int send_soil_data_to_r2(int socket);
int send_alert_temperature_data_to_r2(int socket);
int wait_for_pir();
int get_ultrasonic();
int send_alert_distance_data_to_r2(int socket, int value);


int main(void){

	struct request rcv;
	pid_t pid;
	int socket_r2;
	int time=0;

	/*소켓 초기화*/
	socket_r2 = client_open(R2_ADDR, R2_DATA_PORT,5);
	printf("시작\n");
	pid=fork();
	
	if(pid<0){
		/*fork 안됨.*/
		printf("fork() failed.\n");
	}
	else if(pid==0){
			printf("fork(1)\n");
			while(1){
				printf("보내는 거 시도!\n");
				if(send_light_data_to_r2(socket_r2)<0){
					/*send 실패*/
					printf("light data send() failed.\n");
				}
				/*
				if(send_soil_data_to_r2(socket_r2)<0){
					/*send 실패/* /*
					printf("soil data send() failed.\n");					
				}
				*/
				printf("Sensor send() periodly.\n");
				sleep(PERIOD);
			}
	}
	else{
		pid=fork();
		if(pid<0){
			/*fork 안됨.*/
			printf("fork() failed. (2)\n");
		}
		else if(pid==0){
			printf("fork(2)\n");
			while(1){
				/*PIR 예훈이가 짜야 짠다*/
				if(wait_for_pir()==0){
					while(time<=10){
						time=(clock()/CLOCKS_PER_SEC);
						if(get_ultrasonic()<ALERT_DISTANCE){
							if(send_alert_distance_data_to_r2(socket_r2, get_ultrasonic())<0){
								/*send 실패*/
							}
							break;	
						}
					}
				}
			}					
		}
		else{
			printf("fork(3)\n");			
			while(1){
				if(send_alert_temperature_data_to_r2(socket_r2)<0){
					/*send 실패*/
					
				}
				sleep(TEMPERATURE_PERIOD);
			}			

		}
	}



	client_close(socket_r2);

	return 0;
}

/*r2에게 빛 조도 값 보내는 함수*/
int send_light_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	int len;
	value = read_light_sensor();
	sprintf(data, "%d", value);
	len = sizeof(int);
	rcv = request(socket, 'O', 'l', 's', len, data);

	if(rcv.type=='f'){
		printf("light receive failed.\n");
		return -1;
	}
	else if(rcv.type=='t'){
		printf("light receive timeout.\n");
		return -2;
	}

	return 0;
}

/*r2에게 토양 습도 값을 보내는 함수*/
int send_soil_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	int len;
	value = read_soil_sensor();
	sprintf(data, "%d", value);
	len = sizeof(int);
	rcv = request(socket, 'O', 's', 's', len, data);

	if(rcv.type=='f'){
		printf("soil receive failed.\n");
		return -1;
	}
	else if(rcv.type=='t'){
		printf("soil receive timeout.\n");
		return -2;
	}

	return 0;
}

/*r2에게 온도 값이 일정이상이면 Alert를 보내는 함수*/
int send_alert_temperature_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	int len;
	value = read_dht11_sensor();
	sprintf(data, "%d", value);
	len = sizeof(int);

	/*온도 값이 ALERT_TEMPERATURE 이상일 때 R2에게 데이터 보냄*/
	if(value>ALERT_TEMPERATURE){
		rcv = request(socket, 'O', 't', 's', len, data);
		if(rcv.type=='f'){
			return -1;
		}
		else if(rcv.type=='t'){
			return -2;
		}

	}
	

	return 0;
}


/*pir기다리는 함수*/
int wait_for_pir(){
	
	if(pir_wait()==0){
		return 0;
	}
	else{
		return -1;
	}
}


/*거리 재는 함수*/
int get_ultrasonic(){
	int dist;
	dist = open_ultrasonic_sensor();
	
	return dist;
}


/*r2에게 Alert 신호 보내고 거리 보내는 함수*/
int send_alert_distance_data_to_r2(int socket, int value){
	struct response rcv;
	char data[1024];
	int len;
	sprintf(data, "%d", value);
	len = sizeof(int);
	rcv = request(socket, 'O', 'a', 's', len, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.type=='f'){
		return -1;
	}
	else if(rcv.type=='t'){
		return -2;
	}

	return 0;
}
