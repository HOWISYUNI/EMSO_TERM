#ifndef _NETWORK_H_
#define _NETWORK_H_
#include "../KSF_NET/ksf_net_lib.h"
#endif

#define true 1
#define false 0

int check_led(int data);

void send_led_signal(int socket, int sig);
