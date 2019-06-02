
/* INIT
 * */
int server_init(ip, port);
/* LISTEN
 * */
struct request wait_request(socket);
/* RESPONSE
 * */
int response(socket, type, data);
