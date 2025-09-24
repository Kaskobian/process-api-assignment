#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    pid_t rc = fork();
    if (rc < 0) { perror("fork"); exit(1); }

    if (rc == 0) {
        close(STDOUT_FILENO);
        printf("this likely won't appear on terminal\n");
        fflush(NULL);
        int fd = open("q7_child.out", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd >= 0) {
            printf("now stdout probably points to q7_child.out\n");
            fflush(NULL);
            close(fd);
        }
        _exit(0);
    } else {
        printf("parent still on terminal\n");
    }
    return 0;
}
