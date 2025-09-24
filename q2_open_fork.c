#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
    int fd = open("q2_output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd < 0) { perror("open"); exit(1); }

    pid_t rc = fork();
    if (rc < 0) { perror("fork"); exit(1); }

    const char *who = (rc == 0) ? "child" : "parent";
    for (int i = 0; i < 5; i++) {
        char buf[80];
        int n = snprintf(buf, sizeof(buf), "%s(pid=%d): line %d\n",
                         who, getpid(), i);
        if (write(fd, buf, n) != n) { perror("write"); exit(1); }
        usleep(1000 * 10);
    }
    if (rc != 0) usleep(1000 * 200);
    close(fd);
    return 0;
}
