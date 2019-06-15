#include <stdio.h>
#include <unistd.h>
#include "../../lib/SENSOR/sensor_lib.h"





int main(){

	int value;
	value = read_soil_sensor();

	printf("soil_data : %d\n",value);
	return 0;	
}
