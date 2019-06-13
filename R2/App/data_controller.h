#include <stdio.h>
#include <stdlib.h>

/*network lib*/
#include "../lib/KSF_NET/ksf_net_lib.h"

#define true 1
#define false 0

void send_abnormal_situation_to_r3(int socket, struct request data_r1);

void send_humidity_data_to_r3(int socket, struct request data_r1);

void send_light_data_to_r3(int socket, struct request data_r1);

void send_unidentified_object_to_r3(int socket, struct request data_r1);

int alert_situation();
