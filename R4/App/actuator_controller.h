#include "../lib/ACTUATOR/actuator_lib.h"
#include "../lib/KSF_NET/ksf_net_lib.h"

int led_controller(struct request req);
int led_alert_controller(struct request req);
int buzzer_controller(struct request req);
int camera_controller(struct request req);
int sprinkler_controller(struct request req);
