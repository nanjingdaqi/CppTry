#include <iostream>
#include <stdlib.h>

void my_exit() {
    printf("my_exit\n");
}

int main() {
    atexit(my_exit);
    atexit(my_exit);
    exit(1);
    return 0;
}