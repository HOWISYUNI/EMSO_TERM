#include <unistd.h>		
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
/* Buzzer */
#ifndef BUZZER_DEF
#define BUZZER_DEF

#define BUZZER 25
#define DEV_BUZZER "buzzer"
#define BUZZER_NUM 0x30
#define BUZZER_IOCTL_NUM1 BUZZER_NUM+1
#define BUZZER_IOCTL_NUM2 BUZZER_NUM+2
#define BUZZER_IOCTL_NUM3 BUZZER_NUM+3
#define BUZZER_IOCTL_NUM 'c'
#define BUZZER_ON _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM1, unsigned long *)
#define BUZZER_OFF _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM2, unsigned long *)
#define BUZZER_TIME _IOWR(BUZZER_IOCTL_NUM, BUZZER_IOCTL_NUM3, unsigned long *)
#endif

int main(void){
    int fd;
    fd = open("/dev/buzzer", O_RDWR);

    /* buzzer alert */
    ioctl(fd, BUZZER_ON, 0);    


    close(fd);    
    
    return 0;
}
