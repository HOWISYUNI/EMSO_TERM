#include <sys/fcntl.h>		
#include <unistd.h>		
#include <sys/fcntl.h>
#include <sys/ioctl.h>

/* close */

int turn_on_led();
int turn_off_led(int fd);


int read_light_sensor();

int turn_on_motor();
int turn_off_motor(int fd);
