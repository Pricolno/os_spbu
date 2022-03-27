#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){

    int child_work_file = open("child_work_file.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    int rc = fork();

    if (rc == 0) {
        printf("hello\n");
        write(child_work_file, "yes", 3);

        close(child_work_file);
    }
    else if (rc > 0){
        char buffer[4] = "\0";
        int a = 0;
        while (strcmp(buffer, "yes") != 0){
            child_work_file = open("child_work_file.txt", O_CREAT | O_RDWR, S_IRWXU);
            read(child_work_file, buffer, 3);
        }

        printf("goodbye\n");
    }
    close(child_work_file);
    return 0;
}