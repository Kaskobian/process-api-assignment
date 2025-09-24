#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int p[2];
    if (pipe(p) < 0) { perror("pipe"); exit(1); }

    pid_t rc = fork();
    if (rc < 0) { perror("fork"); exit(1); }

    if (rc == 0) {
        close(p[0]);
        printf("hello\n"); fflush(stdout);
        if (write(p[1], "X", 1) != 1) perror("write");
        close(p[1]);
        _exit(0);
    } else {
        close(p[1]);
        char ch;
        if (read(p[0], &ch, 1) != 1) perror("read");
        close(p[0]);
        printf("goodbye\n");
    }
    return 0;
}
