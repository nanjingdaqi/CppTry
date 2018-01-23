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

int main() {
    char str[80];
    sprintf(str, "This is %d\n", 100);
    printf(str);
    sprintf(str, "That %d\n", 200);
    printf(str);
    return 0;
}