#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>
#include <time.h>

/* camera snapshot */
int main(int argc, char *argv[]){
    int status, ret;
    char file_name[30];
    time_t ts;
    struct tm *t;
    pid_t pid;

    

    /* time stamp min */
    ts = time(NULL);
    t = localtime(&ts);
    sprintf(file_name, "%04d%02d%02d_%02d%02d%02d", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    fprintf(stderr,"snapshot!!: %s\n", file_name);

    pid = fork();
    
    if(pid < 0){
        /* fail to fork */
        printf("fail to fork\n");
        return -1;
    }
    else if(pid == 0){
	
        /* child process */
        execl("/bin/sh", "sh", "./snapshot.sh", file_name, NULL);
    }
    else{
        /* parents process */
        printf("return pid(%d)\n", pid);
        ret = wait(&status);
        printf("snapshot success\n");
        return pid;
    }
}
