#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/time.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {

    if(argc < 2){
        printf("Please provide a 2nd argument\n");
        exit(-1);
    }

    int fd[2];
    pid_t pid;
    size_t BUFFER_SIZE = sizeof(struct timeval);

    if(pipe(fd) == -1){
        perror("PIPE CREATE");
    }

    if( -1 == (pid = fork())){
        perror("FORK");
    }


    if(pid == 0){
        close(fd[READ]);
        struct timeval start_time;
        gettimeofday(&start_time, NULL);
        write(fd[WRITE], &start_time, BUFFER_SIZE);
        execlp(argv[1], argv[2], NULL);
    } else {
        wait(NULL);
        struct timeval end_time;
        gettimeofday(&end_time, NULL);
        close(fd[WRITE]);

        struct timeval* start_time = malloc(BUFFER_SIZE);
        read(fd[READ], start_time, BUFFER_SIZE);

        printf("Elapsed time: %d", end_time.tv_usec - start_time->tv_usec);
    }


    return 0;
}
