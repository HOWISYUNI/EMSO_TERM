#include "actuator_lib.h"
/* LED device path : /dev/LED
   BUZZER device path : /dev/buzzer */

/* turn on led */
int turn_on_led(){
    int fd, ret;
    fd = open("/dev/led", O_RDWR);
    ret = ioctl(fd, TURN_ON_LED, NULL);
    if(ret < 0){
        pritnf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn off led */
int turn_off_led(){
    int fd, ret;
    fd = open("/dev/led", O_RDWR);
    ret = ioctl(fd, TURN_OFF_LED, NULL);
    if(ret < 0){
        pritnf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn on while n sec */
int turn_on_led_timer(unsigned long sec){
    int fd, ret;
    fd = open("/dev/led", O_RDWR);
    ret = ioctl(fd, TIME_LED, sec);
    if(ret < 0){
        pritnf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
/* turn on led alert */
int turn_on_led_alert(){
    int fd, ret;
    fd = open("/dev/led_alert", O_RDWR);
    ret = ioctl(fd, TURN_ON_LED, NULL);
    if(ret < 0){
        pritnf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn off led */
int turn_off_led_alert(){
    int fd, ret;
    fd = open("/dev/led_alert", O_RDWR);
    ret = ioctl(fd, TURN_OFF_LED, NULL);
    if(ret < 0){
        pritnf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn on while n sec */
int turn_on_led_alert_timer(unsigned long sec){
    int fd, ret;
    fd = open("/dev/led_alert", O_RDWR);
    ret = ioctl(fd, TIME_LED, sec);
    if(ret < 0){
        pritnf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
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

/* buzzer on '미' */
int turn_on_buzzer_me(){
	int ret;
	dev = open("/dev/buzzer", O_RDWR);
	ret = ioctl(dev, BUZZER_ME, NULL);

	return ret;	/* success = 0 */
}

/* buzzer on '도' */
int turn_on_buzzer_do(){
	int ret;
	dev = open("/dev/buzzer", O_RDWR);
	ret = ioctl(dev, BUZZER_DO, NULL);

	return ret;	/* success = 0 */
}

/* buzzer off */
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


/* camera snapshot */
int snapshot(void){
    pid_t pid;
    pid = fork();
    
    if(pid < 0){
        /* fail to fork */
        printf("fail to fork\n");
        return -1;
    }
    else if(pid == 0){
        /* child process */
        execl("snapshot.sh", "10230", NULL);
    }
    else{
        /* parents process */
        printf("return pid(%d)\n", pid);
        return pid;
    }
}
