#include <stdio.h>
#include <unistd.h>

#include "app.h"

/*빛 센서/토양 온도 센서 주기를 10초로 설정*/
#define PERIOD 10000
/*온도 체크 주기를 5초로 설정*/
#define TEMPERATURE_PERIOD 5000
/*알람을 뱔생 시킬 온도를 50도(C`)로 설정*/
#define ALERT_TEMPERATURE 50
/*알람을 발생 시킬 거리를 10cm로 설정*/
#define ALERT_DISTANCE 10

int send_light_data_to_r2(int socket);
int send_soil_data_to_r2(int socket);
int send_alert_temperature_data_to_r2(int socket);

int main(void){

	struct request rcv;
	pid_t pid;
	int ret;
	int socket_r2;

	/*소켓 초기화*/
	socket_r2 = client_open(R2_ADDR, R2_DATA_PORT);
	
	pid=fork();

	if(pid<0){
		/*fork 안됨.*/
	}
	else if(pid==0){
			while(1){
				ret=send_light_data_to_r2(socket_r2);
				ret=send_soil_data_to_r2(socket_r2);
				sleep(PERIOD);
			}
	}
	else{
		pid=fork();
		if(pid<0){
			/*fork 안됨.*/
		}
		else if(pid==0){
			while(1){
				/*PIR 예훈이가 짜야 짠다*/
			}					
		}
		else{
			while(1){
				ret=send_alert_temperature_data_to_r2(socket_r2);
				sleep(TEMPERATURE_PERIOD);
			}			

		}
	}

	/*요청 대기*/


	client_close(socket_r2);

	return 0;
}

/*r2에게 빛 조도 값 보내는 함수*/
int send_light_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	value = read_light_sensor();
	sprintf(data, "%d", value);
	len = sizeof(int);
	rcv = request(socket, 'O', 'l', 's', len, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

	return 0;
}

/*r2에게 토양 습도 값을 보내는 함수*/
int send_soil_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	value = read_soil_sensor();
	sprintf(data, "%d", value);
	len = sizeof(int);
	rcv = request(socket, 'O', 's', 's', len, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

	return 0;
}

/*r2에게 온도 값이 일정이상이면 Alert를 보내는 함수*/
int send_alert_temperature_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	value = read_dht11_sensor();
	sprintf(data, "%d", value);
	len = sizeof(int);
	/*온도 값이 ALERT_TEMPERATURE 이상일 때 R2에게 데이터 보냄*/
	if(&data>ALERT_TEMPERATURE){
		rcv = request(socket, 'O', 't', 's', len, data);

	}
	

	return 0;
}

