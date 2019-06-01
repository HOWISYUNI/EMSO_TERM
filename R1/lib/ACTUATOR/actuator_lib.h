#include <sys/fcntl.h>		
#include <unistd.h>		/* close */

int turn_on_led();
int turn_off_led(int fd);

int turn_on_pir();
int turn_off_pir(int fd);

int read_light_sensor();

int turn_on_motor();
int turn_off_motor(int fd);
