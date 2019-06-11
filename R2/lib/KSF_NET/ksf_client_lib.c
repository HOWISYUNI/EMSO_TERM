#include "ksf_client_lib.h"

/* Client REST API */
/* 20190603 aeomhs "rest api - client #interface"
 * Client request to server
 * support method GET / POST / PUT
 * @GET : request send information : select data
 * @PUT : request change something's status : update data
 * @POST: request save information : create new data
 * */


int client_open(char *dest_ip, int port){
    int sock, ret;
    struct sockaddr_in s_addr;
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("failed init\n");
        return -1;
    }
    
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

    //memset(&req, 0, sizeof(req));
    //memset(&rsp, 0, sizeof(rsp));
    
    /* request init */
    req.method = method;
    req.type = type; 
    req.cmd = cmd;   
    req.len = len;
    strcpy(req.data, data);

    /* send request */
    ret = write(sock, &req, sizeof(struct request));
    if(ret < 0){
        /* fail request */
        rsp.type = 'f';
        rsp.len = 0;
        strcpy(rsp.data, "send request fail\n");
        return rsp;
    }
    
    /* maybe wait until receive response */
    ret = read(sock, &rsp, sizeof(struct response));
    if(ret < 0){
        /* fail request */
        rsp.type = 'f';
        rsp.len = 0;
        strcpy(rsp.data, "receive response fail\n");
        return rsp;
    }

    return rsp;
}

int client_close(int sock){
    int ret;
    ret = close(sock);
    
    return ret;
}
