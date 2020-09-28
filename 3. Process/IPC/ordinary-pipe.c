#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 20
#define READ_END 0
#define WRITE_END 1

int main() {
    const int fd[2];
    pid_t pid;

    char WRITE_MESSAGE[BUFFER_SIZE] = "Hello Message";
    char READ_MESSAGE[BUFFER_SIZE];

    if(pipe(fd) < 0){
        perror("Unable to create pipe\n");
    }

    if((pid = fork()) < 0){
        perror("Unable to create process\n");
    }

    if(pid > 0){
        close(fd[READ_END]);
        write(fd[WRITE_END], WRITE_MESSAGE, strlen(WRITE_MESSAGE));
        close(fd[WRITE_END]);
        printf("Parent Write Success\n");
        wait(NULL);
    } else {
        close(fd[WRITE_END]);
        read(fd[READ_END], READ_MESSAGE, BUFFER_SIZE);
        printf("Child read: %s\n", READ_MESSAGE);
        close(fd[READ_END]);
    }
    return 0;
}
