#include "actuator_lib.h"

#include <time.h>
/* LED device path       : /dev/LED
   LED_ALERT device path : /dev/LED_ALERT
   BUZZER device path    : /dev/buzzer    */

/* turn on led */
int turn_on_led(void){
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
int turn_off_led(void){
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
int turn_on_led_alert(void){
    int fd, ret;
    fd = open("/dev/led_alert", O_RDWR);
    ret = ioctl(fd, TURN_ON_LEDA, NULL);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn off led */
int turn_off_led_alert(void){
    int fd, ret;
    fd = open("/dev/led_alert", O_RDWR);
    ret = ioctl(fd, TURN_OFF_LEDA, NULL);
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
    ret = ioctl(fd, TIME_LEDA, sec);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* turn on buzzer */
int turn_on_buzzer(void){
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
int turn_off_buzzer(void){
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
    prinkler lib
    on
    off 
    timer - can but after finish kernel panic (bad pc value)
*/
int turn_on_sprinkler(void){
	int fd_m, fd_w;
    fd_m = open("/dev/motor", O_RDWR);
    fd_w = open("/dev/water_pump", O_RDWR);
    /* motor running */
    ioctl(fd_m, MOTOR_ON, 0);    
    /* water_pump running */
    ioctl(fd_w, PUMP_ON, 0);

    close(fd_m);    
    close(fd_w);

    return 0;
}

int turn_off_sprinkler(void){
	int fd_m, fd_w;
    fd_m = open("/dev/motor", O_RDWR);
    fd_w = open("/dev/water_pump", O_RDWR);
    /* motor stop */
    ioctl(fd_m, MOTOR_OFF, 0);    
    /* water_pump stop */
    ioctl(fd_w, PUMP_OFF, 0);

    close(fd_m);    
    close(fd_w);

    return 0;
}

int timer_sprinkler(unsigned long sec){
	int fd_m, fd_w;
    fd_m = open("/dev/motor", O_RDWR);
    fd_w = open("/dev/water_pump", O_RDWR);
    /* motor stop */
    ioctl(fd_m, MOTOR_TIMER, sec);    
    /* water_pump stop */
    ioctl(fd_w, PUMP_TIMER, sec);

    close(fd_m);    
    close(fd_w);

    return 0;
}



/* camera snapshot */
int snapshot(char *file_name){
    pid_t pid;
    pid = fork();
    
    if(pid < 0){
        /* fail to fork */
        printf("fail to fork\n");
        return -1;
    }
    else if(pid == 0){
        /* child process */
        execl("/bin/sh", "sh", "./snapshot.sh", file_name, NULL);
    }
    else{
        /* parents process */

        /* No wait Camera Snapshot
        printf("wait...\n");
        ret = wait(&status);    
        if(ret < 0){
            printf("failed child exit\n");
            return -1;
        }
        printf("snapshot success\n");
        */
        return pid;
    }
}
