#include <iostream>
#include <unistd.h>
#include <signal.h>

void print_tid() {
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("pid: %d, tid %ld\n", pid, tid);
}

void sig_handler(int sig) {
    printf("Handling sig by tid: %ld\n", pthread_self());
    exit(100);
}

void* thread_run(void* args) {
    printf("args: %s, ", args);
    print_tid();
    sleep(5);
}

int main() {
//    printf("pid: %d\n", getpid());
//    printf("ppid: %d\n", getppid());
//    printf("uid: %d\n", getuid());

    struct sigaction act, oact;
    act.sa_handler = sig_handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    printf("Sig result %d\n", sigaction(SIGUSR1, &act, &oact));

    print_tid();

    pthread_t pt;
    for (int i = 0; i < 10; ++i) {
        char* s = new char[10];
        sprintf(s, "Thread %d", i);
        pthread_create(&pt, NULL, thread_run, (void *) s);
    }

    while(1) {
        printf("loop\n");
        sleep(5);
    }

//    int pid;
//    if ((pid = fork()) < 0) {
//        printf("fork fail\n");
//    } else if (pid == 0) {
//        printf("Child process: %d\n", getpid());
//        printf("exec returns: %d\n", execlp("cp", ""));
//    } else {
//        printf("Parent process: %d\n", getpid());
//        int status;
//        while(wait(&status) < 0) {
//            printf("wait fail\n");
//        }
//        printf("child died\n");
//    }

    return 0;
}