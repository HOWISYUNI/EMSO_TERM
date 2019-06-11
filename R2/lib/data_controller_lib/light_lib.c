#include "./light_lib.h"

/*r1으로부터 통신 대기*/
/*int wait_light_data_from_r1(){

	return 0;
}*/

/*r1으로부터 데이터 수신*/
/*int recieve_light_data_from_r1(){

	return 0;
}*/

/*r3에 연결 요청*/
/*int request_connection_to_r3(){

	return 0;
}*/

/*r3에 빛 데이터 전송*/
void send_light_data_to_r3(int socket, struct response data_r1){
	struct response rcv;

	rcv = request(socket, 'O', 'l', 's', data_r1.len, data_r1.data);

	/*추후 예외처리를 할지도 모르니 만들어는 놨는데 비어둠*/
	if(rcv.data){

	}

}
