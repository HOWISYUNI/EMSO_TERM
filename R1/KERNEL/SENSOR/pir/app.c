#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../../../lib/SENSOR/sensor_lib.h"

#define ALERT_DISTANCE 10


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



int main(){
	int time = 0;

	while(1){
			/*PIR 예훈이가 짜야 짠다*/
			if(wait_for_pir()==0){
				while(time<=10){
					time=(clock()/CLOCKS_PER_SEC);
					printf("distance : %d\n",get_ultrasonic());
					if(get_ultrasonic()<ALERT_DISTANCE){
						printf("%d\n",time);
						break;	
					}
				}
			}
		}	

	return 0;	
}
