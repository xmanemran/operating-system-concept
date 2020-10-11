#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define shm "max23"
#define BUFFER_SIZE 4096

int main(int argc, char* argv[]) {

    if(argc < 2){
        printf("Please provide 2nd argument\n");
        exit(-1);
    }

    pid_t pid;
    int n = atoi(argv[1]);

    if(n == 0){
        printf("2nd argument have to be a valid integer and grater then 0\n");
        exit(-1);
    }

    int shm_fd;
    if(0 > (shm_fd = shm_open(shm, O_RDWR | O_CREAT, 0777))){
        perror("CREATE SHM FILE");
    }

    ftruncate(shm_fd, BUFFER_SIZE);
    char* shm_ptr = mmap(0, BUFFER_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    char* ref = shm_ptr;
    if(shm_ptr == NULL){
        perror("CREATING (mmap)");
    }

    if(-1 == (pid = fork())){
        perror("CREATE CHILD");
        exit(errno);
    }

    if(pid == 0){
        int count = sprintf(shm_ptr, "%d ", n);
        shm_ptr+= count;

        while(n > 1){
            if(n % 2 == 0) n /= 2;
            else n = 3 * n + 1;
            count = sprintf(shm_ptr, "%d ", n);
            shm_ptr+= count;
        }
        count = sprintf(shm_ptr, "\n");
        shm_ptr+= count;
    } else {
        wait(NULL);
        printf("%s", ref);
    }

    shm_unlink(shm);
    return 0;
}
