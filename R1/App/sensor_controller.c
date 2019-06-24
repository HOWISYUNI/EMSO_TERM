#include "sensor_controller.h"

int send_light_data_to_r2(int socket);
int send_soil_data_to_r2(int socket);
int send_alert_temperature_data_to_r2(int socket, int value);
int wait_for_pir();
int get_ultrasonic();
int send_alert_distance_data_to_r2(int socket, int value);
int emergency_actuator_signal(void);

static int ultra_fd;


int main(void){

	struct request rcv;
	pid_t pid;
	int socket_r2;
	int distance=0;
	int time=0;
	int tmpo;

	/*소켓 초기화*/
	ultra_fd = open_ultrasonic_sensor();


	pid=fork();
	
	if(pid<0){
		/*fork 안됨.*/
		printf("fork() failed.\n");
	}
	else if(pid==0){
			while(1){
				printf("1. 조도 값, 습도 값 보내는 거 시도!\n");
				socket_r2 = client_open(R2_ADDR, R2_DATA_PORT,WAIT_RSP);	
				if(send_light_data_to_r2(socket_r2)<0){
					/*send 실패*/
					printf("1. light data send() failed.\n");
				}
				client_close(socket_r2);
				sleep(1);				
				socket_r2 = client_open(R2_ADDR, R2_DATA_PORT,WAIT_RSP);
				if(send_soil_data_to_r2(socket_r2)<0){
					/*send 실패*/
					printf("1. soil data send() failed.\n");					
				}

				client_close(socket_r2);
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
			while(1){
				/*PIR 예훈이가 짜야 짠다*/
				if(wait_for_pir()==0){
					printf("2. PIR 발견.\n");
					time = 0;
					distance = -1;
					while(time<=10){
						fprintf(stderr, "time : %d\n", time);
						/*time=(clock()/CLOCKS_PER_SEC);*/
						distance = get_ultrasonic();
						if(distance<ALERT_DISTANCE&&distance>0){
                            emergency_actuator_signal();
						    //printf("notify emergency to r4\n");
						    
							socket_r2 = client_open(R2_ADDR, R2_DATA_PORT,WAIT_RSP);
							printf("2. 침입 알람 R2에게 전송\n");	
							if(send_alert_distance_data_to_r2(socket_r2, distance)<0){
								/*send 실패*/
							}
							client_close(socket_r2);
							break;	
						}
						time++;
						sleep(1);
					}
					/* find err */
					//fprintf(stderr, "time : distance = %d : %d\n", time, distance);
				}
			}					
		}
		else{
			while(1){
				printf("3. 온도 측정!\n");
				tmpo = read_dht11_sensor();
				if(tmpo > ALERT_TEMPERATURE){
			        emergency_actuator_signal();
            	    //printf("notify emergency to r4\n");
                	    
				    socket_r2 = client_open(R2_ADDR, R2_DATA_PORT,10);
				    if(send_alert_temperature_data_to_r2(socket_r2, tmpo)<0){
					    /*send 실패*/
					    
				    }
				    client_close(socket_r2);
				}
				sleep(TEMPERATURE_PERIOD);
			}			

		}
	}

	close_ultrasonic_sensor(ultra_fd);

	

	return 0;
}

/*r2에게 빛 조도 값 보내는 함수*/
int send_light_data_to_r2(int socket){
	struct response rcv;
	char data[1024];
	int value;
	int len;
	value =0;
	value = read_light_sensor();
	sleep(1);
	sprintf(data, "%d", value);
	len = sizeof(data);
	rcv = request(socket, POST, LIGHT, STORE, len, data);
	printf("1. light : %d\n",value);
	if(rcv.type==FAILURE){
		printf("1. light receive failed.\n");
		return -1;
	}
	else if(rcv.type==TIME_OUT){
		printf("1. light receive timeout.\n");
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
	value=0;
	value = read_soil_sensor();
	sleep(1);
	printf("1. soil : %d\n",value);	
	sprintf(data, "%d", value);
	len = sizeof(data);
	rcv = request(socket, POST, SOIL, STORE, len, data);

	if(rcv.type==FAILURE){
		printf("1. soil receive failed.\n");
		return -1;
	}
	else if(rcv.type==TIME_OUT){
		printf("1. soil receive timeout.\n");
		return -2;
	}

	return 0;
}

/*r2에게 온도 값이 일정이상이면 Alert를 보내는 함수*/
int send_alert_temperature_data_to_r2(int socket, int value){
	struct response rcv;
	char data[1024];
	int len;
		
	sprintf(data, "%d", value);
	len = sizeof(data);

	/*온도 값이 ALERT_TEMPERATURE 이상일 때 R2에게 데이터 보냄*/

	rcv = request(socket, POST, EMG_T, STORE, len, data);
	printf("3. 온도 이상 현재 온도 : %d 도 \n",value);
	if(rcv.type==FAILURE){
		return -1;
	}
	else if(rcv.type==TIME_OUT){
		return -2;
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
	int fd;
	dist = read_ultrasonic_sensor(ultra_fd);
	
	return dist;
}


/*r2에게 Alert 신호 보내고 거리 보내는 함수*/
int send_alert_distance_data_to_r2(int socket, int value){
	struct response rcv;
	char data[1024];
	int len;
	
	printf("2. 거리 : %d\n",value);
	sprintf(data, "%d", value);
	len = sizeof(data);
	rcv = request(socket, POST, EMG_P, STORE, len, data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.type==FAILURE){
		return -1;
	}
	else if(rcv.type==TIME_OUT){
		return -2;
	}
    
	return 0;
}

/* Emergency situation, send signal to R4 */
int emergency_actuator_signal(void){
    char file_name[20];
    int sock, ret;
    time_t ts;
    struct tm *t;
    struct response rsp;

    /* time stamp */
    ts = time(NULL);
    t = localtime(&ts);
    sprintf(file_name, "%04d%02d%02d_%02d%02d%02d", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    
    sock = client_open(R4_ADDR, R4_ACT_PORT, WAIT_RSP);
    
    /* Fail Connect */
    if(sock < 0)
        return -1;
    
    rsp = request(sock, PUT, EMERGENCY, TURN_ON, sizeof(file_name), file_name);
    
    /* Fail request */
    if(rsp.type != SUCCESS)
        return -1;
    
    client_close(sock);
    
    return 0;
}

