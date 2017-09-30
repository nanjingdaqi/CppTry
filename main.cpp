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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}