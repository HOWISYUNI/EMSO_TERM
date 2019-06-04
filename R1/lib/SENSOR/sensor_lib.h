#include <sys/fcntl.h>		
#include <unistd.h>		/* close */

/* sensor library header */

int turn_on_pir();
int turn_off_pir(int fd);

int turn_on_ultrasonic();
int turn_off_ultrasonic(int fd);
