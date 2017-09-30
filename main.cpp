#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF_SIZE 10

void quit(char* msg, int exit_code) {
    size_t len = strlen(msg);
    char suffix[] = ": %d";
    char* buffer = static_cast<char *>(malloc(len + strlen(suffix)));
    strcpy(buffer, msg);
    strcat(buffer, suffix);
    printf(buffer, errno);
    exit(exit_code);
}

int main() {
    int fds[2];
    if (pipe(fds) == -1) {
        quit("pipe fail", -1);
    }
    pid_t pid = fork();
    if (pid == -1) {
        quit("for fail", -1);
    }
    if (pid == 0) {
        // child
        if (close(fds[1]) == -1) {
            quit("close write fd fail", -1);
        }
        int numRead;
        char buf[BUF_SIZE];
        for (;;) {
            numRead = read(fds[0], buf, BUF_SIZE);
            if (numRead == -1) {
                quit("read from pipe fail", -1);
            }
            if (numRead == 0) {
                printf("read is over\n");
                break;
            }
            if (write(STDOUT_FILENO, buf, numRead) != numRead) {
                quit("std out fail", -1);
            }
        }
        if (close(fds[0]) == -1) {
            quit("close read pipe fail", -1);
        }
    } else {
        // parent
        if (close(fds[0]) == -1) {
            quit("close read fd fail", -1);
        }
        char content[] = "Hello pipe\n";
        for (int i = 0; i < 3; ++i) {
            if (write(fds[1], content, strlen(content)) == -1) {
                quit("fail to write pip", -1);
            }
            printf("parent sleep\n");
            sleep(3);
        }
        if (close(fds[1]) == -1) {
            quit("fail to close write pipe", -1);
        }
        wait(NULL);
        printf("parent ends\n");
    }
    return 0;
}