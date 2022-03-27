#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int rc = fork();
    
    if (rc == 0){
        printf("Child is working\n");
        printf("PID: %d\n", getpid());
        exit(0);
    }
    else if (rc > 0){
        int status;
        waitpid(rc, &status, 0);
        printf("Parent is working\n");
        printf("PID: %d\n", getpid());        
    }
    else{
        fprintf(stderr, "fork failed");
    }
}