#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t rc = fork();
    if (rc < 0) { perror("fork"); exit(1); }

    if (rc == 0) {
        printf("child(pid=%d): finishing\n", getpid());
        _exit(42);
    } else {
        int status = 0;
        pid_t got = wait(&status);
        if (got < 0) { perror("wait"); exit(1); }
        printf("parent(pid=%d): wait() -> pid=%d, WIFEXITED=%d, status=%d\n",
               getpid(), got, WIFEXITED(status),
               WIFEXITED(status) ? WEXITSTATUS(status) : -1);
    }
    return 0;
}
