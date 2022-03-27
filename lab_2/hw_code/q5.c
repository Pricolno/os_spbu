#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int rc = fork();

    if (rc == 0){
        int wc = wait(NULL);
        printf("Child is working\n");
        printf("Result of wait: %d\n", wc);
    }
    else if (rc > 0){
        printf("Parent is working\n");
    }
    else{
        fprintf(stderr, "fork failed");
    }
}