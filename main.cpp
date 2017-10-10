#include <iostream>
#include <string.h>

void quit(char* msg, int exit_code) {
    size_t len = strlen(msg);
    char suffix[] = ": %d";
    char* buffer = static_cast<char *>(malloc(len + strlen(suffix)));
    strcpy(buffer, msg);
    strcat(buffer, suffix);
    printf(buffer, errno);
    exit(exit_code);
}

void* thread_run(void* args) {
    pthread_t tid = pthread_self();
    printf("start run in thread: %ld\n", tid);
    printf("args is: %s\n", (char*) args);
}

int main() {
    pthread_t pid;
    int ret = pthread_create(&pid, NULL, thread_run, (void* )"Hello thread");
    if (ret != 0) {
        quit("pthread_create fail", -1);
    }
    pthread_join(pid, NULL);
    return 0;
}