#include <unistd.h>		
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

/* LED Alert */
#ifndef LED_ALERT_DEF
#define LED_ALERT_DEF

/* LED ALERT RGB */
#define LED_R 16
#define LED_G 20
#define LED_B 21
#define DEV_LED_ALERT "led_alert"

#define LED_ALERT_IOCTL 0x20
#define LED_ALERT_IOCTL_NUM1 LED_ALERT_IOCTL+1
#define LED_ALERT_IOCTL_NUM2 LED_ALERT_IOCTL+2
#define LED_ALERT_IOCTL_NUM3 LED_ALERT_IOCTL+3
#define LED_ALERT_IOCTL_NUM 'b'
#define TURN_ON_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM1, unsigned long *)
#define TURN_OFF_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM2, unsigned long *)
#define TIME_LEDA _IOWR(LED_ALERT_IOCTL_NUM, LED_ALERT_IOCTL_NUM3, unsigned long *)

#endif

int main(void){
    int fd;
    fd = open("/dev/led_alert", O_RDWR);

    /* led alert */
    ioctl(fd, TURN_OFF_LEDA, 0);    


    close(fd);    
    
    return 0;
}
