#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int x = 100;

    int rc = fork();

    if (rc == 0) {
        printf("------------------------------------\n");
        printf("Child\n");
        printf("------------------------------------\n");
        printf("1_Value of x: %d\n", x);
        x = 500;
        printf("2_Value of x: %d\n", x);
    }

    else if (rc > 0) {
        wait(NULL);
        printf("------------------------------------\n");
        printf("Parent\n");
        printf("------------------------------------\n");
        printf("1_Value of x: %d\n", x);
        x = 700;
        printf("2_Value of x: %d\n", x);
    }
    else {
        fprintf(stderr, "fork failed");
    }
}