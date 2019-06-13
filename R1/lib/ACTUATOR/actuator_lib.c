#include "actuator_lib.h"
#include <stdio.h>
/* LED device path : /dev/LED
   BUZZER device path : /dev/buzzer */

/* turn on led */
int turn_on_led(){
    int fd, ret;
    fd = open("/dev/led", O_RDWR);
    ret = ioctl(fd, TURN_ON_LED, NULL);
    if(ret < 0){
        printf("failed\n");
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
        printf("failed\n");
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
        printf("failed\n");
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
        printf("failed\n");
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
        printf("failed\n");
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
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn on buzzer */
int turn_on_buzzer(){
    int fd, ret;
    fd = open("/dev/buzzer", O_RDWR);
    ret = ioctl(fd, BUZZER_ON, NULL);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
/* turn off buzzer */
int turn_off_buzzer(){
    int fd, ret;
    fd = open("/dev/buzzer", O_RDWR);
    ret = ioctl(fd, BUZZER_OFF, NULL);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
/* turn on buzzer while n sec*/
int turn_on_buzzer_timer(unsigned long sec){
    int fd, ret;
    fd = open("/dev/buzzer", O_RDWR);
    ret = ioctl(fd, BUZZER_TIME, sec);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
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
