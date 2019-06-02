/* Server REST API */
/* 20190602 aeomhs "rest api - server #interface"
 * Server is always on.
 * support method GET / POST / PUT
 * @GET : request send information : select data
 * @PUT : request change something's status : update data
 * @POST: request save information : create new data
 * */

int server_init(ip, port){
    struct server_info s_info;
    int socket, ret;

    /* server init */
    s_info.ip = ip;
    s_info.port = port;

    /* socket init */
    ret = ioctl(socket, INIT_SERVER, s_info);
    if(ret < 0){
        /* fail init */
        return -1;
    }

    return socket;
}

/* Server should be run alyways */
struct request wait_request(socket){
    struct request req;

    /* server running : Listen */
        while(1){
            /* Wait request */
            req = read(socket, request);

            return req;
        }
}

/* Send response */
int response(socket, type, data){
    struct response rsp;
    int ret;

    /* response init */
    rsp.type = type;
    rsp.data = data;

    /* send response */
    ret = write(socket, rsp, sizeof(struct response));
    if(ret < 0){
        /* fail response */
    }

    return ret;
}


/********************************************************/

/* GET : response refined data 
 * return : result value
 * parameter : type, data 
 * request from : R2.cmd_ctl.client */
int response_get(socket, type, data){
    struct response rsp;
    int ret;

    /* response init */
    rsp.type = type;
    rsp.data = data;

    /* send response */
    ret = write(socket, rsp, sizeof(struct response));
    if(ret < 0){
        /* fail response */
    }

    return ret;
}

/* POST : response save result
 * return : result value
 * parameter : type, data 
 * request from : R1.sensor_ctl.client 
 * request from : R2.data_ctl.client
 * */
int response_post(socket){

}

/* PUT : reponse changed status
 * return : result value
 * parameter : type, dev, status 
 * request from : R2.cmd_ctl.client
 * */
int response_put(socket){

}
