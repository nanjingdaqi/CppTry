#include <iostream>
#include <signal.h>
#include <unistd.h>

void sig_handler(int sig) {
    printf("get sig %d\n", sig);
    exit(100);
}

int main() {
    printf("sigchld %d\n", SIGCHLD);
    printf("pid: %d\n", getpid());

//    struct sigaction sig = {
//            .sa_handler = sig_handler,
//            .sa_flags = 0,
//    };
    struct sigaction sig;
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    sigemptyset(&sig.sa_mask);

    struct sigaction oact;
    printf("sig result: %d\n", sigaction(3, &sig, &oact));

    while(1) {
        printf("loop\n");
        sleep(5);
    }

    return 0;
}