#include <sys/fcntl.h>		
#include <unistd.h>		/* close */

int turn_on_led();
int turn_off_led(int fd);

int turn_on_pir();
int turn_off_pir(int fd);
