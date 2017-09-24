#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
//    printf("pid: %d\n", getpid());
//    printf("ppid: %d\n", getppid());
//    printf("uid: %d\n", getuid());

    int pid;
    if ((pid = fork()) < 0) {
        printf("fork fail\n");
    } else if (pid == 0) {
        printf("Child process: %d\n", getpid());
        printf("exec returns: %d\n", execlp("cp", ""));
    } else {
        printf("Parent process: %d\n", getpid());
        int status;
        while(wait(&status) < 0) {
            printf("wait fail\n");
        }
        printf("child died\n");
    }

    return 0;
}