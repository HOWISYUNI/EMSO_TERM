#include "device_lib.h"
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

int turn_on_pir(){
	int ret;
	ret = open("/dev/pir", O_RDWR);
	
	return ret;	/* success : 0 */
}

int turn_off_pir(int fd){
	int ret;
	ret = close(fd);

	return ret;	/* success : 0 */
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

/*
	motor turn on
	counter-clockwise 180 -> clockwise 360 -> counter-clockwise 360
*/
int turn_on_motor(){
	int ret;
	ret = open("/dev/motor_dev", O_RDWR);
	return ret;
}

/*turn off motor*/
int turn_off_motor(int fd){
	int ret;
	ret = close(fd);
	return ret;
}
