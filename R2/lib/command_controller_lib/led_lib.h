#include "../KSF_NET/ksf_server_lib.h"
#include "../KSF_NET/ksf_client_lib.h"

#define true 1
#define false 0

int check_led(int data);

void send_led_signal(int socket, int sig);
