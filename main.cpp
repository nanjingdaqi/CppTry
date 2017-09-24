#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {

    int fd = open("foo.txt", O_RDWR|O_CREAT, S_IWUSR|S_IRUSR);
    printf("fd: %d\n", fd);
    char* buf = "Hello C";
    int sz = write(fd, buf, 7);
    printf("write res: %d", sz);
    close(fd);

    return 0;
}