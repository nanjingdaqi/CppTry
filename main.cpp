#include <iostream>
#include <string.h>

void quit(char *msg, int exit_code) {
    size_t len = strlen(msg);
    char suffix[] = ": %d";
    char *buffer = static_cast<char *>(malloc(len + strlen(suffix)));
    strcpy(buffer, msg);
    strcat(buffer, suffix);
    printf(buffer, errno);
    exit(exit_code);
}

void foo(int arg[]) {
    printf("arg len: %d\n", sizeof(arg));
}

int main() {
//    int *pi = new int;
//    *pi = 100;
//    printf("pi: %d\n", pi);
//    delete pi;
//    printf("pi: %d\n", pi);
//    printf("pi: %d\n", *(pi));
//    printf("pi: %d\n", *(pi + 100000));

    int *pa = new int[10];
    printf("pa: %d\n", *(pa));
    printf("pa: %d\n", *(pa+1));
    printf("pa: %d\n", *(pa+9));
    printf("pa: %d\n", *(pa+10));

    foo(pa);

    return 0;
}