#include "sprinkler.h"

int main(void){
    int fd_w;
    
    fd_w = open("/dev/water_pump", O_RDWR);

    /* water_pump on timer */
    ioctl(fd_w, PUMP_TIMER, 10);

    close(fd_w);
}
