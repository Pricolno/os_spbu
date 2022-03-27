#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    int rc = fork();

    if (rc == 0) {
        printf("Child work on ls\n");
        char* argv[] = {"ls", NULL};
        char* envp[] = {NULL};

    
        execl("/bin/ls", "ls", NULL); // arg as list 
        //execlp("ls", "ls", NULL); // find in PATH
        //execle("/bin/ls", "ls", NULL, envp); 
        //execv("/bin/ls", argv); // arg as vector
        //execvp("ls", argv); 
        
    }
    else if (rc > 0){
        wait(NULL);
    }
    else{
        fprintf(stderr, "fork failed");
    }
}