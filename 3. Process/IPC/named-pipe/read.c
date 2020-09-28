#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define myfifo "/Users/emran/Desktop/myfifo"
#define BUFFER_SIZE 80

int main() {

    int pipe_fd;
    char stdin_buff[BUFFER_SIZE];
    size_t len;

    while(1){
        pipe_fd = open(myfifo, O_RDONLY);
        if(0 > (len = read(pipe_fd, stdin_buff, BUFFER_SIZE))){
            perror("READ");
        }

        if(len > 0){
            printf("Admin: %s", stdin_buff);
        }

        close(pipe_fd);
    }
    return 0;
}
