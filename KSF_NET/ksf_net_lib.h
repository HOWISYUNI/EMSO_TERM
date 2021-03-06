#ifndef STANDARD_LIB
#define STANDARD_LIB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

#ifndef KSF_NET_CONF
#define KSF_NET_CONF
#define R1_ADDR "10.10.10.13"
#define R2_ADDR "10.10.10.14"
#define R2_DATA_PORT 4010 /* Server */
#define R3_ADDR "10.10.10.15"
#define R3_STG_PORT 5010  /* Server */
#define R3_REF_PORT 5020  /* Server */
#define R4_ADDR "10.10.10.16"
#define R4_ACT_PORT 6020  /* Server */
#define LOCAL_HOST "127.0.0.1"
#define LOCAL_PORT 4000
#define BACK_LOG_N 4      /* backlog : number of queue can listen to connection  */
#define WAIT_RSP 10
#endif

#ifndef KSF_NET_DEFINE
#define KSF_NET_DEFINE

/* Method */
#define GET  'G'
#define POST 'O'
#define PUT  'U'
/* Device type */
/* SENSOR */
#define LIGHT     'L'
#define SOIL      'S'
#define EMG_T     'T'
#define EMG_P     'P'
/* ACTUATOR */ 
#define LED       'l'
#define LED_ALERT 'a'
#define BUZZER    'b'
#define CAMERA    'c'
#define SPRINKLER 's'
#define EMERGENCY 'e'
#define FIN_EMRCY 'f'

/* Command */
/* GET */
#define RCNT_VAL    'v'
#define AVERAGE     'a'
/* POST */
#define STORE       'S'
/* PUT */
#define TURN_ON     1
#define TURN_OFF    0

/* RESPONSE TYPE */
#define FAILURE     'F'
#define TIME_OUT    'T'
#define SUCCESS     'S'

#endif

#ifndef KSF_NET_METHOD
#define KSF_NET_METHOD
struct request{
    char method;
    char type;
    char cmd;
    unsigned long len;
    char data[BUFF_SIZE];
};

struct response{
    char type;
    unsigned long len;
    char data[BUFF_SIZE];
};
#endif

#ifndef KSF_CLIENT_FUNC
#define KSF_CLIENT_FUNC
/* Client Function */
int client_open(char *dest_ip, int port, long timeout);
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);
int client_close(int sock);
#endif

#ifndef KSF_SERVER_FUNC
#define KSF_SERVER_FUNC
/* Server Function */
int server_open(int port);
int server_close(int sock);
int wait_request(int sock, struct request *req);
int response(int c_sock, char type, unsigned long len, char *data);
#endif
