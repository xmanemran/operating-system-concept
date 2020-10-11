#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

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

    if(-1 == (pid = fork())){
        perror("CREATE CHILD");
        exit(errno);
    }

    if(pid == 0){
        printf("%d ", n);
        while(n > 1){
            if(n % 2 == 0) n /= 2;
            else n = 3 * n + 1;
            printf("%d ", n);
        }
        printf("\n");
    } else {
        wait(NULL);
    }

    return 0;
}


