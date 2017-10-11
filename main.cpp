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

#define T_SIZE 10
int g_i = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* thread_run(void* args) {
    pthread_mutex_lock(&mtx);
    printf("g_i: %d\n", g_i++);
    pthread_mutex_unlock(&mtx);
}

int main() {
    pthread_t pids[T_SIZE];
    for (int i = 0; i < T_SIZE; ++i) {
        pthread_t pid;
        int ret = pthread_create(&pid, NULL, thread_run,
                                 (void *) "Hello thread");
        if (ret != 0) {
            quit("pthread_create fail", -1);
        }
        pids[i] = pid;
    }
    for (int i = 0; i < T_SIZE; ++i) {
        pthread_join(pids[i], NULL);
    }
    return 0;
}