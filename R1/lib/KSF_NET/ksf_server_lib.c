#include "ksf_server_lib.h"

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
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        printf("failed init\n");
        return -1;
    }
    
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    ret = bind(sock, (struct sockaddr*)&s_addr, sizeof(s_addr));
    
    if(ret < 0){
        printf("failed bind\n");
        return -1;
    }

    return sock;
}

int server_close(int sock){
    int ret;
    
    ret = close(sock);

    return ret;
}

/* Server should be run alyways */
int wait_request(int sock, struct request *req){
    int ret;
    int c_sock; /* client socket */
    int c_addr_size;
    struct sockaddr_in c_addr; /* client address */
    
    ret = listen(sock, 5);
    if(ret < 0){
        printf("failed listen\n");
        return -1;
    }
    
    c_addr_size = sizeof(struct sockaddr_in);
    c_sock = accept(sock, (struct sockaddr*)&c_addr, &c_addr_size);
    
    if(c_sock < 0){
        printf("failed connect to client\n");
        return -1;
    }
    
    read(c_sock, req, sizeof(struct request));
    printf("received\n");
    
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
    
    write(c_sock, &rsp, sizeof(struct response));
    close(c_sock);

    return 0;
}

