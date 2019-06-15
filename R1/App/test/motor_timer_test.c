#include "sprinkler.h"
#include <unistd.h>

int main(void){
    int fd;
    fd = open("/dev/motor", O_RDWR);
    
    /* motor on */
    ioctl(fd, MOTOR_TIMER, 10);    

    close(fd);    
}
