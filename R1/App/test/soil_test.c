#include <stdio.h>

#include "../../lib/SENSOR/sensor_lib.h"

int main(void){
	int soil_data;
	
	soil_data = read_light_sensor();

	printf("%d\n",soil_data);

	return 0;
}
