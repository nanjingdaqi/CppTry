#include <iostream>
#include <stdlib.h>
#include <unistd.h>


int main() {
//    printf("pid: %d\n", getpid());
//    printf("ppid: %d\n", getppid());
//    printf("uid: %d\n", getuid());

    int pid;
    if ((pid = fork()) < 0) {
        printf("fork fail\n");
    } else if (pid == 0) {
        printf("Child process: %d\n", getpid());
    } else {
        printf("Parent process: %d\n", getpid());
    }

    return 0;
}