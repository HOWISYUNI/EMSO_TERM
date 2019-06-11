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


/* turn on  buzzer*/
int turn_on_buzzer(){
    int ret;
    ret = open("/dev/buzzer", O_RDWR);
    return ret;
}

/* turn off buzzer*/
int turn_off_buzzer(int fd){
    int ret;
    ret = close(fd);
    return ret;
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
