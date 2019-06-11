#include <stdio.h>
#include <unistd.h>

#include "app.h"

int main(void){
    printf("led on\n");
    led_controller(1);
    sleep(5);
    printf("led off\n");
    led_controller(0);
    return 0;
}
