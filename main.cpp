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

int* g_i;

void check_uninit_pt() {
    printf("g_i: %d", g_i);
    printf("g_i val: %d", *g_i);
}

int main() {
    check_uninit_pt();
    return 0;
}