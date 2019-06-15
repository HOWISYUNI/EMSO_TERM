#include <unistd.h>		
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>

int turn_on_motor(){
	int ret;
	ret = open("/dev/motor", O_RDWR);
	return ret;
}

/*turn off motor*/
int turn_off_motor(int fd){
	int ret;
	ret = close(fd);
	return ret;
}

int main(){
	int a=0;
	int fd=0;
	
	while(1){
		a=0;
		printf("1. on 2. off\n");
		scanf("%d",&a);
		if(a==1){
			fd=turn_on_motor();
		}else if(a==2){
			turn_off_motor(fd);
		}
	}


}
