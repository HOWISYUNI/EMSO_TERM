#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>

/* camera snapshot */
int main(int argc, char *argv[]){
    int status, ret;
    pid_t pid;
    pid = fork();
    
    if(pid < 0){
        /* fail to fork */
        printf("fail to fork\n");
        return -1;
    }
    else if(pid == 0){
        /* child process */
        execl("/bin/sh", "sh", "./snapshot.sh", argv[1], NULL);
    }
    else{
        /* parents process */
        printf("return pid(%d)\n", pid);
        printf("wait...\n");
        ret = wait(&status);    
        if(ret < 0){
            printf("failed child exit\n");
            return -1;
        }
        printf("snapshot success\n");
        return pid;
    }
}
