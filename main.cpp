#include <iostream>
#include <string.h>
#include <fcntl.h>

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

void testOpenMode() {
    open("tmp.txt", O_WRONLY | O_CREAT);
}

int main() {
    testOpenMode();
    return 0;
}