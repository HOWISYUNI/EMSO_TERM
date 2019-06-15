#include "sprinkler.h"

int main(void){
    int fd_m, fd_w;
    fd_m = open("/dev/motor", O_RDWR);
    fd_w = open("/dev/water_pump", O_RDWR);
    /* motor run on timer */
    ioctl(fd_m, MOTOR_TIMER, 10);    
    /* water_pump on timer */
    ioctl(fd_w, PUMP_TIMER, 10);

    close(fd_m);    
    close(fd_w);
}
