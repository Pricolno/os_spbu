#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct stat sb;
    int file = open("file.txt", O_CREAT | O_RDWR, S_IRWXU);
    
    int rc = fork();

    if (rc == 0){
        char* child_letter = "Child's letter\n";
        printf("________Child are writing________\n");
        write(file, child_letter , strlen(child_letter));
        exit(0);
    }
    else if (rc > 0){
        wait(NULL);
        char * parent_letter = "Parent's letter\n";
        printf("________Parent is writing________\n");
        write(file, parent_letter, strlen(parent_letter));
    }
    
    close(file);
    return 0;
}