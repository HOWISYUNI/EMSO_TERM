#include <stdio.h>
#include <unistd.h>

#include "app.h"

int main(void){
	printf("led on\n");
	led_controller(1);
	sleep(5);
	printf("led off\n");
	led_controller(0);

	printf("Buzzer on\n");
	buzzer_controller(10, 0);
	sleep(10);
	printf("Buzzer off\n");
	buzzer_controller(0, 1);

	return 0;
}

