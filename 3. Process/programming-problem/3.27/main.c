/*
 * Design a file-copying program named filecopy.c using ordinary pipes.
 * This program will be passed two parameters: the name of the file to be copied and the name of the destination file.
 * The program will then create an ordinary pipe and write the contents of the file to be copied to the pipe.
 * The child process will read this file from the pipe and write it to the destination file.
 * For example, if we invoke the program as follows:
 * ./filecopy input.txt copy.txt
 * the file input.txt will be written to the pipe.
 * The child process will read the contents of this file and write it to the destination file copy.txt.
 * You may write this program using either UNIX or Windows pipes.
 * (c) Emran <xmanemran@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 500
#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {

    if(argc < 3){
        printf("Please provide source file and destination file and \n");
        exit(-1);
    }

    pid_t pid;
    char* source_path = argv[1];
    char* destination_path = argv[2];

    int pipe_fd[2];
    if(pipe(pipe_fd) < 0){
        perror("CREATE PIPE FD ");
        exit(errno);
    }

    if(-1 == (pid = fork())){
        perror("CREATE CHILD");
        exit(errno);
    }

    if(pid == 0){
        close(pipe_fd[WRITE_END]);
        char buffer[BUFFER_SIZE];
        int len = 0, fd;

        fd = open(destination_path, O_RDWR | O_CREAT | O_TRUNC, 0777);

        while(0 < (len = read(pipe_fd[READ_END], buffer, BUFFER_SIZE))){

            if(len < 0){
                perror("PIPE READ ");
                exit(errno);
            }

            int wr_len;
            wr_len = write(fd, buffer, len);

            if(wr_len < 0){
                perror("WRITE FILE ");
                exit(errno);
            }
        }
        close(fd);
        close(pipe_fd[READ_END]);

    } else {
        close(pipe_fd[READ_END]);
        int fd = open(source_path, O_RDONLY);
        if(fd < 0){
            perror("SOURCE FILE OPEN: ");
            exit(errno);
        }

        char buffer[BUFFER_SIZE];
        int len;
        while( 0 < (len = read(fd, buffer, BUFFER_SIZE))){

            int wr_len = write(pipe_fd[WRITE_END], buffer, len);

            if(wr_len < 0){
                perror("WRITE PIPE ");
                exit(errno);
            }
        }

        if(len == -1){
            perror("SOURCE READ ");
            exit(errno);
        }
        close(fd);
        close(pipe_fd[WRITE_END]);
        wait(NULL);
        printf("Write complete\n");
    }

    return 0;
}


