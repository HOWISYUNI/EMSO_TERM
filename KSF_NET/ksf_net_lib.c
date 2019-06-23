#include "ksf_net_lib.h"


/* Client REST API */
/* 20190603 aeomhs "rest api - client #interface"
 * Client request to server
 * support method GET / POST / PUT
 * @GET : request send information : select data
 * @PUT : request change something's status : update data
 * @POST: request save information : create new data
 * */


int client_open(char *dest_ip, int port, long timeout){
    int sock, ret;
    struct sockaddr_in s_addr;
    struct timeval wait_time;        /* timeout value */
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("failed init\n");
        return -1;
    }
    
    /* Socket option*/
    wait_time.tv_sec = timeout;
    wait_time.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&wait_time, sizeof(wait_time));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&wait_time, sizeof(wait_time));
    
    /* hdr set */
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = inet_addr(dest_ip);
    
    ret = connect(sock, (struct sockaddr*)&s_addr, sizeof(s_addr));
    if(ret < 0){
        printf("failed connect\n");
        return -1;
    }
    
    return sock;
}

struct response request(int sock, char method, char type, char cmd, unsigned long len, char *data){
    struct request req;
    struct response rsp;
    int ret;

    /* request init */
    req.method = method;
    req.type = type; 
    req.cmd = cmd;   
    req.len = len;
    strcpy(req.data, data);

    /* printf("request : %c %c %c %ld %s\n", req.method, req.type, req.cmd, req.len, req.data); */
    
    /* send request */
    ret = write(sock, &req, sizeof(struct request));
    if(ret < 0){
        /* fail request */
        rsp.type = 'f';
        rsp.len = 0;
        strcpy(rsp.data, "send request fail\n");
        return rsp;
    }

    /* printf("request success\n"); */
    
    /* maybe wait until receive response */
    ret = read(sock, &rsp, sizeof(struct response));
    if(ret < 0){
        /* fail request */
        rsp.type = 'f';
        rsp.len = 0;
        strcpy(rsp.data, "receive response fail\n");
        return rsp;
    }
    
    /* printf("response : %c %ld %s\n", rsp.type, rsp.len, rsp.data); */

    return rsp;
}

int client_close(int sock){
    int ret;
    ret = close(sock);
    /*
    if(ret < 0)
        printf("client socket close failed\n");
    */
    return ret;
}

/* Server REST API */
/* 20190602 aeomhs "rest api - server #interface"
 * Server is always on.
 * support method GET / POST / PUT
 * @GET : request send information : select data
 * @PUT : request change something's status : update data
 * @POST: request save information : create new data
 * */

int server_open(int port){
    int sock, ret;
    struct sockaddr_in s_addr;  /* server address */
    int reuse_port = 1;         /* port reuse */
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("failed init\n");
        return -1;
    }
    
    /* socket option */
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse_port, sizeof(reuse_port));
    
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    ret = bind(sock, (struct sockaddr*)&s_addr, sizeof(s_addr));
    
    if(ret < 0){
        printf("failed bind\n");
        return -1;
    }
    
    ret = listen(sock, BACK_LOG_N);
    if(ret < 0){
        printf("failed listen\n");
    }

    return sock;
}

int server_close(int sock){
    int ret;
    
    ret = close(sock);
    /*
    if(ret < 0)
        printf("server socket close failed\n");
    */
    
    return ret;
}

/* Server should be run alyways */
int wait_request(int sock, struct request *req){
    int ret;
    int c_sock; /* client socket */
    int c_addr_size;
    struct sockaddr_in c_addr; /* client address */   
    
    /* wait for connection from client */
    c_addr_size = sizeof(struct sockaddr_in);
    c_sock = accept(sock, (struct sockaddr*)&c_addr, &c_addr_size);
    
    if(c_sock < 0){
        printf("failed connect to client\n");
        return -1;
    }
    
    /* read buffer net socket io queue */
    read(c_sock, req, sizeof(struct request));

    /*printf("request : %c %c %c %ld %s\n", req->method, req->type, req->cmd, req->len, req->data);*/

    return c_sock;
}

/* Send response */
int response(int c_sock, char type, unsigned long len, char *data){
    struct response rsp;
    int ret;
    
    /* response init */
    rsp.type = type;
    rsp.len = len;
    memset(rsp.data, 0, BUFF_SIZE);
    strcpy(rsp.data, data);
    
    /*printf("response : %c %ld %s\n", rsp.type, rsp.len, rsp.data);*/
    
    write(c_sock, &rsp, sizeof(struct response));

    /*printf("response success\n");*/
    
    close(c_sock);

    return 0;
}

