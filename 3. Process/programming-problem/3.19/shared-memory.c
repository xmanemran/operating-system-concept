#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/time.h>

#define shm_name "/max"

int main(int argc, char *argv[]) {

    if(argc < 2){
        printf("Please provide a 2nd argument\n");
        exit(-1);
    }

    int shm_file;
    if(0 > (shm_file = shm_open(shm_name, O_RDWR | O_CREAT, 0777))){
        perror("SHM OPEN");
        exit(errno);
    }
    ftruncate(shm_file, sizeof(struct timeval));

    pid_t pid;

    if(0 > (pid = fork())){
        perror("Fork");
        exit(errno);
    }

    if(pid > 0){
        wait(NULL);
        struct timeval *start_time;
        struct timeval current_time;
        gettimeofday(&current_time,  NULL);
        start_time = (struct timeval *) mmap(0, sizeof(struct timeval), PROT_READ, MAP_SHARED, shm_file, 0);
        printf("Elapsed time: %ld", current_time.tv_usec  - start_time->tv_usec);
    } else {
        struct timeval *current_time;
        current_time = (struct timeval *) mmap(0, sizeof(struct timeval),  PROT_WRITE, MAP_SHARED, shm_file, 0);
        gettimeofday(current_time,  NULL);
        execlp(argv[1], argv[2], NULL);
    }

    return 0;
}
