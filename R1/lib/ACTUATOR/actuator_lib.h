#include <sys/fcntl.h>		
#include <unistd.h>		/* close */

int turn_on_led();
int turn_off_led(int fd);

int turn_on_buzzer();
int turn_off_buzzer(int fd);

int read_light_sensor();
