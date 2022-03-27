#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int rc = fork();

    if (rc == 0){
        printf("Child is working\n");
        close(STDOUT_FILENO);
        printf("Try to write\n");
    }
    else if (rc > 0){
        wait(NULL);
        printf("Parent is working\n");
    }
    else {
        printf("fork failed\n");
    }
}