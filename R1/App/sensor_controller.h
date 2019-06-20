#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "../lib/SENSOR/sensor_lib.h"
#include "../../KSF_NET/ksf_net_lib.h"

#define PERIOD 10                   /*빛 센서/토양 온도 센서 주기를 10초로 설정*/
#define TEMPERATURE_PERIOD 5        /*온도 체크 주기를 5초로 설정*/
#define ALERT_TEMPERATURE 50        /*알람을 뱔생 시킬 온도를 50도(C`)로 설정*/
#define ALERT_DISTANCE 10           /*알람을 발생 시킬 거리를 10cm로 설정*/
#define DIST_SECONDS 10             /*PIR신호가 왔을 때 거리를 재는 시간을 10초로 설정*/
