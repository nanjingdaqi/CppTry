#include <iostream>
#include <string.h>
#include <unistd.h>

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
        quit("pipe create error", -1);
    }
    int pid = fork();
    if (pid == 0) {
        // child
        if (close(fds[1]) == -1) {
            quit("child close write fail", -1);
        }
        int nfds = fds[0] + 1;
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(fds[0], &readfds);
        int ret = select(nfds, &readfds, NULL, NULL, NULL);
        if (ret == -1) {
            quit("child select fail", -1);
        }
        printf("child select returns: %d\n", ret);
        char buf[10];
        if (!FD_ISSET(fds[0], &readfds)) {
            quit("fds[0] is not in readfds", -1);
        }
        if (read(fds[0], buf, 1) == -1) {
            quit("read fds[0] fail", -1);
        }
        printf(buf);
    } else {
        // parent
        if (close(fds[0] == -1)) {
            quit("parent close read fail", -1);
        }
        sleep(3);
        if (write(fds[1], "H", 1) == -1) {
            quit("parent write fail", -1);
        }
    }
}