#include "pir.h"

int main(void){
    int fd, ret;
    fd = open("/dev/pir", O_RDWR);
    ret = ioctl(fd, DETECT_WAIT, NULL);
    printf("return value : %d\n", ret);
    close(fd);

    return 0;
} 
