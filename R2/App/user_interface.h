#include <stdio.h>
#include <stdlib.h>

/*네트워크 라이버러리*/
#include "../lib/KSF_NET/ksf_net_lib.h"

#define BUF 1024
#define true 1
#define false 0

void send_sprinkler_signal(int socket, int sig);

void send_led_signal(int socket, int sig);

void request_soil_recent_to_r3(int socket, char* str);

void request_light_recent_to_r3(int socket, char* str);

int request_soil_average_to_r3(int socket);

int request_light_average_to_r3(int socket);

void parse(char* str);
