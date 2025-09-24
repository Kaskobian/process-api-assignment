#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t c1 = fork();
    if (c1 < 0) { perror("fork"); exit(1); }
    if (c1 == 0) { _exit(10); }

    pid_t c2 = fork();
    if (c2 < 0) { perror("fork"); exit(1); }
    if (c2 == 0) { sleep(1); _exit(20); }

    int st;
    pid_t got = waitpid(c2, &st, 0);
    printf("parent: waitpid(c2) -> pid=%d, status=%d\n",
           got, WIFEXITED(st) ? WEXITSTATUS(st) : -1);
    wait(NULL);
    return 0;
}
