#include "sprinkler.h"
#include <unistd.h>

int main(void){
    int fd;
    fd = open("/dev/motor", O_RDWR);
    
    /* motor on */
    ioctl(fd, MOTOR_ON, 0);    

    close(fd);    
}
