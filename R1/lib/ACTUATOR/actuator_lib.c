#include "actuator_lib.h"
/* LED device path : /dev/LED */

/* turn on led */
int turn_on_led(){
    int ret;
    ret = open("/dev/led", O_RDWR);
    return ret;
}

/* turn off led */
int turn_off_led(int fd){
    int ret;
    ret = close(fd);
    return ret;
}

int turn_on_buzzer(){
	int ret;
	ret = open("/dev/buzzer", O_RDWR);
	return ret;
}

int turn_off_buzzer(int fd){
	int ret;
	ret = close(fd);
	return ret;
}

/* read value from light sensor*/
int read_light_sensor(){
	int dev;
	int ret;
	int light_value=0;

	dev = open("/dev/light_sensor_dev",O_RDWR);
	
	ret=read(dev,&light_value,sizeof(int));
	
	ret = close(dev);

	return light_value;
}
