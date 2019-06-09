#include "ksf_net.h"

/* INIT : client socket init
 * return : result value
 * parameter : ip, port
 * */
int client_open(char *dest_ip, int port);

/* GET : request refined data
 * return : response
 * parameter : type, data, cmd
 * usage : R2.cmd_ctl.client->R3.refine_ctl.server
 * */
/* POST : request create data
 * return : response
 * parameter : type, data
 * usage : R1.sensor_ctl.client->R2.data_ctl.server
 * usage : R2.data_ctl.client->R3.storage_ctl.server
 * */
/* PUT : request update data
 * return : response
 * parameter : type, data, cmd
 * usage : R2.cmd_ctl.client->R1.act_ctl.server
 * */
struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data);

int client_close(int sock);
