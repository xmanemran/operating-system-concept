#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define myfifo "/Users/emran/Desktop/myfifo"
#define BUFFER_SIZE 80

int main() {

    int pipe_fd;
    char stdin_buff[BUFFER_SIZE];

    remove(myfifo);
    if(0 > mkfifo(myfifo, 0777)){
        perror("CREATE FIFO");
        exit(errno);
    }

    while(1){
        pipe_fd = open(myfifo, O_RDWR);
        printf("Instruction: ");
        fgets(stdin_buff, BUFFER_SIZE, stdin);
        if(0 > write(pipe_fd, stdin_buff, strlen(stdin_buff) + 1)){
            perror("WRITE");
            exit(errno);
        }
        close(pipe_fd);
    }
    return 0;
}
