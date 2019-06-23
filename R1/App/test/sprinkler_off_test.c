#include "sprinkler.h"

int main(void){
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
