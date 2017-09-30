#include <iostream>
#include <sys/inotify.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

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
    int inotifyFd;
    inotifyFd = inotify_init();
    if (inotifyFd == -1) {
        printf("inotify_init fail, %d", errno);
        exit(-1);
    }
    char target_file[] = "/home/daqi/tmp/miui.apk";
    int wd = inotify_add_watch(inotifyFd, target_file, IN_ALL_EVENTS);
    if (wd == -1) {
        printf("add_watch fail, %d", errno);
        exit(-1);
    }
    int num_read;
    char buf[BUF_LEN];
    char* p;
    inotify_event* event;
    for (;;) {
        num_read = read(inotifyFd, buf, BUF_LEN);
        if (num_read == 0) {
            quit("read fail", -1);
        }
        for (p = buf; p < buf + num_read;) {
            event = reinterpret_cast<inotify_event *>(p);
            p += sizeof(struct inotify_event) + event->len;
            printf("event wd: %d, mask: %d, cookie: %d, len: %d\n", event->wd, event->mask, event->cookie, event->len);
        }
    }
    return 0;
}