#include <unistd.h>		
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <signal.h>

#define SPRINKLER_ON _IOWR(SPRINKLER_IOCTL_NUM, SPRINKLER_IOCTL_NUM1, unsigned long *)
#define SPRINKLER_OFF _IOWR(SPRINKLER_IOCTL_NUM, SPRINKLER_IOCTL_NUM2, unsigned long *)
#define SPRINKLER_DELAY _IOWR(SPRINKLER_IOCTL_NUM, SPRINKLER_IOCTL_NUM3, unsigned long *)
#define SPRINKLER_NUM 0x30
#define SPRINKLER_IOCTL_NUM1 SPRINKLER_NUM+1
#define SPRINKLER_IOCTL_NUM2 SPRINKLER_NUM+2
#define SPRINKLER_IOCTL_NUM3 SPRINKLER_NUM+3
#define SPRINKLER_IOCTL_NUM 'c'


int turn_on_sprinkler();
int turn_off_sprinkler();
int turn_on_sprinkler_timer(unsigned long sec);
static int fd,ret;

int main(void)
{
	int a,b;
	int status;
	pid_t pid;
	pid=fork();
	while(1){
		a=0;
		b=0;
		
		if(pid<0){
			printf("fork() failed.\n");
		}
		else if(pid==0){
			printf("1. On 2. Timer 3. Off\n");
			scanf("%d",&a);
			if(a==1){
				printf("ON\n");
				if(turn_on_sprinkler()<0){
					printf("fail\n");
				}else{
					printf("turn on().\n");
				}
			}
			else if(a==2){
				printf("Enter Timer\n");
				scanf("%d",&b);
				if(b>0){
					if(turn_on_sprinkler_timer(b)<0){
						printf("fail\n");
					}else{
						printf("turn on timer().\n");
					}
				}
			}
			else if(a==3){
				if(turn_off_sprinkler()<0){
					printf("fail\n");
				}else{
					printf("turn off().\n");
				}
				printf("OFF\n");
				kill(pid,SIGINT);
			}
		}
		else{
			wait(&status);
		}
	}
	return 0;
}

int turn_on_sprinkler(){
//    int fd, ret;
    fd = open("/dev/sprinlker", O_RDWR);
    ret = ioctl(fd, SPRINKLER_ON, NULL);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
int turn_off_sprinkler(){
//    int fd, ret;
    fd = open("/dev/sprinlker", O_RDWR);
    ret = ioctl(fd, SPRINKLER_OFF, NULL);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int turn_on_sprinkler_timer(unsigned long sec){
//    int fd, ret;
    fd = open("/dev/sprinkler", O_RDWR);
    ret = ioctl(fd, SPRINKLER_DELAY, sec);
    if(ret < 0){
        printf("failed\n");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}
