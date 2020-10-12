#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096
#define READ_END 0
#define WRITE_END 1

int main(int argc, char* argv[]) {

    pid_t pid;
    int write_child_fd[2];
    int write_parent_fd[2];
    char message[BUFFER_SIZE] = "Python Basics Video Course now on Youtube! Watch Now.";

    if(pipe(write_child_fd) < 0){
        perror("CREATE CHILD PIPE ");
        exit(errno);
    }
    if(pipe(write_parent_fd) < 0){
        perror("CREATE PARENT PIPE ");
        exit(errno);
    }

    if(-1 == (pid = fork())){
        perror("CREATE CHILD ");
        exit(errno);
    }

    if(pid == 0){
        // close unnecessary fd
        close(write_parent_fd[READ_END]);
        close(write_child_fd[WRITE_END]);

        // read parent message
        char rc_message[BUFFER_SIZE];
        int len = read(write_child_fd[READ_END], rc_message, BUFFER_SIZE);
        if(len <= 0){
            perror("READING CHILD FROM CHILD ");
            exit(errno);
        } else {

            // reverse parent message
            --len;
            int ccode;
            char send_message[BUFFER_SIZE];
            while(len >= 0){
                ccode = (int) rc_message[len];
                if(64 < ccode && ccode < 91) {
                    send_message[len] = (char) (ccode + 32);
                } else if (96 < ccode && ccode < 123){
                    send_message[len] = (char) (ccode - 32);
                } else {
                    send_message[len] = (char) ccode;
                }
                len--;
            }

            // send reversed message to the child.
            len = write(write_parent_fd[WRITE_END], send_message, BUFFER_SIZE);
            if(len < 0){
                perror("WRITING PARENT FROM CHILD ");
                exit(errno);
            }
        }
    } else {
        // close unnecessary fd
        close(write_parent_fd[WRITE_END]);
        close(write_child_fd[READ_END]);

        //  write to the child
        int len = write(write_child_fd[WRITE_END], message, BUFFER_SIZE);
        if(len < 0){
            perror("WRITING CHILD FROM PARENT ");
            exit(errno);
        }

        // waiting for child return
        wait(NULL);

        // read child message
        char buffer[BUFFER_SIZE];
        len = read(write_parent_fd[READ_END], buffer, BUFFER_SIZE);
        if(len <= 0){
            perror("READING PARENT FROM PARENT ");
            exit(errno);
        } else {
            printf("%s\n", buffer);
        }
    }

    return 0;
}
