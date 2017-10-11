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

void* thread_read(void* args) {
    int* fds = (int*) args;
    int nfds = fds[0] + 1;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(fds[0], &readfds);
    printf("begin selecting\n");
    int s = select(nfds, &readfds, NULL, NULL, NULL);
    if (s == -1) {
        quit("select readfds fail", -1);
    }
    printf("select returns\n");
    char buf[20];
    s = read(fds[0], buf, 1);
    if (s == -1) {
        quit("read fds[0] fail\n", -1);
    }
    printf("get msg: %s\n", buf);
}

void* thread_write(void* args) {
    int* fds = (int*) args;
    sleep(3);
    int s = write(fds[1], "H", 1);
    if (s < 0) {
        quit("write to fds[1] fail\n", -1);
    }
}

int main() {
    int fds[2];
    if (pipe(fds) == -1) {
        quit("pipe create error", -1);
    }

    pthread_t t_r, t_w;
    int s = pthread_create(&t_r, NULL, thread_read, fds);
    if (s != 0) {
        quit("pthread_create fail", -1);
    }
    s = pthread_create(&t_w, NULL, thread_write, fds);
    if (s != 0) {
        quit("pthread_create fail", -1);
    }
    pthread_join(t_r, NULL);
    pthread_join(t_w, NULL);
    return 0;
}