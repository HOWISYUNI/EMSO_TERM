/* Client REST API */
/* 20190603 aeomhs "rest api - client #interface"
 * Client request to server
 * support method GET / POST / PUT
 * @GET : request send information : select data
 * @PUT : request change something's status : update data
 * @POST: request save information : create new data
 * */


int client_init(char *dest_ip, int port){
    int sock, ret;
    struct sockaddr_in server_addr;
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("failed init\n");
        return -1;
    }
    
    /* hdr set */
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(dest_ip);
    
    ret = connect(sock, (struct *sockaddr)&server_addr, sizeof(struct sockaddr_in));
    if(ret < 0){
        printf("failed connect\n");
        return -1;
    }
    
    return sock;
}

struct response request_get(int sock, char type, char *data, char cmd){
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
