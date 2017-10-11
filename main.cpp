#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

struct ep_arg {
    int epfd;
    int* fds;
};

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
    ep_arg* ep_a = (ep_arg*) args;
    int* fds = ep_a->fds;
    int epfd = ep_a->epfd;

    epoll_event ev;
    ev.data.fd = fds[0];
    ev.events = EPOLLIN;
    int s = epoll_ctl(epfd, EPOLL_CTL_ADD, fds[0], &ev);
    if (s == -1) {
        quit("epoll add event fail", -1);
    }

    printf("start epoll waiting\n");
    epoll_event ev_list[5];
    s = epoll_wait(epfd, ev_list, 5, -1);
    if (s == -1) {
        quit("epoll wait fail", -1);
    }

    char buf[1];
    s = read(fds[0], buf, 1);
    if (s == -1) {
        quit("read fds[0] fail\n", -1);
    }
    printf("get msg: %s\n", buf);
}

void* thread_write(void* args) {
    ep_arg* ep_a = (ep_arg*) args;
    int* fds = ep_a->fds;
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
    int epfd = epoll_create(5);
    if (epfd == -1) {
        quit("epoll_create fail", -1);
    }
    ep_arg arg;
    arg.epfd = epfd;
    arg.fds = fds;

    pthread_t t_r, t_w;
    int s = pthread_create(&t_r, NULL, thread_read, &arg);
    if (s != 0) {
        quit("pthread_create fail", -1);
    }
    s = pthread_create(&t_w, NULL, thread_write, &arg);
    if (s != 0) {
        quit("pthread_create fail", -1);
    }
    pthread_join(t_r, NULL);
    pthread_join(t_w, NULL);
    return 0;
}