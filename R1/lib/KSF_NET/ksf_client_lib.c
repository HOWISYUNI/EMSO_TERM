/* Client REST API */
/* 20190603 aeomhs "rest api - client #interface"
 * Client request to server
 * support method GET / POST / PUT
 * @GET : request send information : select data
 * @PUT : request change something's status : update data
 * @POST: request save information : create new data
 * */


int client_init(src_ip, dest_ip, port, type){
    struct client_info c_info;
    struct server_info s_info;
    int socket, ret;
    socket = open("/dev/ksf_net_client", O_RDWR);

    /* client init */
    c_info.ip = src_ip;
    c_info.port = port;
    c_info.type = type; /* @GET @POST @PUT */

    /* set dest server */
    s_info.ip = dest_ip;
    s_info.port = port;

    /* socket init */
    ret = ioctl(socket, INIT_CLIENT, c_info);
    if(ret < 0){
        /* fail init */
        return -1;
    }
    /* ask alive server */
    ret = ioctl(socket, INIT_CONNCT, s_info);
    if(ret < 0){
        /* cannot connect to server */
        return -2;
    }

    return socket;
}

struct response request_get(socket, type, data, cmd){
    struct request req;
    struct response rsp;
    int ret;

    /* request init */
    req.type = type; /* @light @soil */
    req.data = data; /* @60 == 현재로부터 1시간 전부터 계산 */
    req.cmd = cmd;   /* @avg @sum ... */
    req.method = GET;

    /* send request */
    ret = write(socket, req, sizeof(struct request));
    if(ret < 0){
        /* fail request */
    }

    /* maybe wait until receive response */
    ret = read(socket, rsp, sizeof(struct response));
    if(ret < 0){
        /* fail request */
    }

    return rsp;
}

struct response request_post(socket, type, data){
    struct request req;
    struct response rsp;
    int ret;
    /* request init */
    req.type = type; /* @light @soil @alert */
    req.data = data; /* @data : ...? */
    req.cmd = NULL;
    req.method = POST;

    /* send reqeust */
    ret = write(socket, req, sizeof(struct requset));
    if(ret < 0){
        /* fail request */
    }

    /* wait response */
    ret = read(socket, rsp, sizeof(struct response));
    if(ret < 0){
        /* fail request */
    }

    return rsp;
}

struct response request_put(socket, type, data, cmd){
    struct request req;
    struct response rsp;
    int ret;
    /* request init */
    req.type = type; /* @led @motor @pump @buzzer @camera @led */
    req.data = data; /* @60 : 60min */
    req.cmd = cmd;   /* @on @off */
    req.method = PUT;

    /* send reqeust */
    ret = write(socket, req, sizeof(struct request));
    if(ret < 0){
        /* fail request */
    }

    /* wait response */
    ret = read(socket, rsp, sizeof(struct response));
    if(ret < 0){
        /* fail request */
    }

    return rsp;
}
