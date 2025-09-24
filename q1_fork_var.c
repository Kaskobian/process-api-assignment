#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int x = 100;
    printf("parent(pid=%d): before fork, x=%d\n", getpid(), x);

    pid_t rc = fork();
    if (rc < 0) { perror("fork"); exit(1); }

    if (rc == 0) {
        printf(" child(pid=%d): initial x=%d\n", getpid(), x);
        x = 200;
        printf(" child(pid=%d): after child writes, x=%d\n", getpid(), x);
        _exit(0);
    } else {
        x = 300;
        printf("parent(pid=%d): after parent writes, x=%d\n", getpid(), x);
    }
    return 0;
}
