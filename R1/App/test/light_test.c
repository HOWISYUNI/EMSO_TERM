#include <stdio.h>
#include <unistd.h>
#include "../../lib/SENSOR/sensor_lib.h"





int main(){

	int value;
	value = read_light_sensor();

	printf("light_data : %d\n",value);
	return 0;	
}
