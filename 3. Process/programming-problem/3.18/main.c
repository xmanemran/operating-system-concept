#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    pid_t pid;

    if(0 > (pid = fork())) {
        perror("Process Create");
        exit(errno);
    }

    if(pid > 0){
        printf("I am the parent\n");
        printf("My child PID: %d\n", (int) pid);
        sleep(100);
    }

    return 0;
}
