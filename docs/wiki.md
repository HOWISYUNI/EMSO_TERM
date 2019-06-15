

# Definition Device


## Device GPIO num 

```C
#define LED 4          /*  led  */
#define LED_ALERT 5    /* led_alert */
#define MOTOR_A 6      /* motor */
#define CE0 8          /* light */
#define CE1 7          /* soil */
#define MISO 9         /* light */
#define MOSI 10        /* light */
#define SCLK 11        /* light */
#define MOTOR_B 13     /* motor */
#define SENSOR 17      /*  pir  */
#define MOTOR_C 19     /* motor */
#define DHT 21         /* dht11 */
#define MOTOR_D 26     /* motor */
#define BUZZER 25      /* buzzer*/
#define WATERPUMP_A 12   /*waterpump */
#define WATERPUMP_B 24    /*waterpump*/
#define TRIG 23        /* UltraSonic */
#define ECHO 27        /* UltraSonic */
```

## Device name
```C
#define DEV_LED "led"
#define DEV_DHT "dht11"
#define DEV_LIGHT "light"
#define DEV_PIR "pir"
```

---

# Network (Data Communictation)
> RESTful Library  
> Client request to server  
> Server response to client  
## Server function lib
```C
int server_open(int port);                                           /* socket open & bind */
int server_close(int sock);                                          /* socket close */
int wait_request(int sock, struct request *req);                     /* connect(listen,accpet) & read */
int response(int c_sock, char type, unsigned long len, char *data);  /* write */
```
## Client function lib
```C
int client_open(char *dest_ip, int port, long timeout);                                            /* socket open & connect */
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);/* write & read */
int client_close(int sock);                                                                        /* socket close */
```

## Request struct
```C
struct request{
    char method;          /* Request Method */
    char type;            /* Data Type */
    char cmd;             /* Command */
    unsigned long len;    /* Real Data length */
    char data[BUFF_SIZE]; /* BUFF_SIZE = 1024 */
};
```

### @GET
```
> Usage  : R2.cmd_ctl.client->R3.refine_ctl.server
> method : 'G' (should be fixed)
> type   : light('l'), soil('s'), alert_log('a')  
> cmd    : value('v'), average('a'), sum('s')  
> len    : data length  
> data   :   
```
### @POST
```
> Usage  : R1.sensor_ctl.client->R2.data_ctl.server  
>        : R2.data_ctl.client->R3.storage_ctl.server  
> method : 'O' (should be fixed)  
> type   : light('l'), soil('s'), alert_log('a')  
> cmd    : save('s')  
> len    : data length   
> data   :   
```
### @PUT
```
> Usage  : R2.cmd_ctl.client->R1.act_ctl.server  
> method : 'U' (should be fixed)  
> type   : led_light('l'), led_alert('a'), buzzer('b')  
>           , camera('c'), motor('m'), water_pump('p'), sprinkler('s'),    
> cmd    : turn_on('1'), turn_off('0')  
> len    : data length  
> data   : timer(positive), infinit(zero), error(negative)
```
## Response struct
```C
struct response{
    char type;            /* Request Result */
    unsigned long len;    /* Real Data length */
    char data[BUFF_SIZE]; /* BUFF_SIZE = 1024 */
};
```
```
> Usage  : Successful('s'), Failure('f'), Timeout('t')  
> len    : data length  
> data   :   
```
---

# Dictionary

1. Device
 > Sensor + Actuator
2. Sensor
 > 특정한 값을 읽어들이거나, 인터럽트를 감지하는 장치
3. Actuator
 > 제어 신호를 통해서, 움직이는 동적인 장치
4. ctl
 > Controller 약어


