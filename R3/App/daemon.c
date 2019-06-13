/* daemon */

int storage_controller(int ip, int port){
	int socket;

	socket = server_init(ip, port);

	pthread(wait_request);
}

ptread(){
	response();
}


