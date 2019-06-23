#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    int fd, ret;
    int buf;
    
    fd = open("/dev/light_sensor_dev", O_RDWR);
    if(fd < 0){
        printf("fail open\n");
    }
    
    ret = read(fd, &buf, sizeof(int));
    if(ret < 0){
        printf("fail read\n");
    }
    
    printf("soil : %d\n", buf);
    close(fd);
    return 0;
}
