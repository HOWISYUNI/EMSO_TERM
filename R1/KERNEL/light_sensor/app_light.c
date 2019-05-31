#include <device_lib.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
	int light_value;

	light_value=read_light_sensor();	

	printf("light sensor : %d\n",light_value);
	    
}

