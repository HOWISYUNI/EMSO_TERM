#include "dht11_lib.h"

int turn_on_dht11(){
	int ret;

	ret = open("/dev/dht11", O_RDWR);

	return ret;
}

int turn_off_dht11(int fd){
	int ret;

	ret = close(fd);

	return ret;
}
