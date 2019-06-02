
/* INIT : client init
 * return : result value
 * parameter : ip, port, type/dev?
 * */
int client_init(src_ip, dest_ip, port, type);

/* GET : request refined data
 * return : response
 * parameter : type, data, cmd
 * usage : R2.cmd_ctl.client->R3.refine_ctl.server
 * */
struct response request_get(socket, type, data, cmd);

/* POST : request create data
 * return : response
 * parameter : type, data
 * usage : R1.sensor_ctl.client->R2.data_ctl.server
 * usage : R2.data_ctl.client->R3.storage_ctl.server
 * */
struct response request_post(socket, type, data);

/* PUT : request update data
 * return : response
 * parameter : type, data, cmd
 * usage : R2.cmd_ctl.client->R1.act_ctl.server
 * */
struct response request_put(socket, type, data, cmd);
