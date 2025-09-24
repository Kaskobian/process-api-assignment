#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
extern char **environ;

static void run_variant(const char *which) {
    if (strcmp(which, "execl") == 0) {
        execl("/bin/ls", "ls", "-l", (char*)NULL);
    } else if (strcmp(which, "execle") == 0) {
        char *envp[] = { "LC_ALL=C", NULL };
        execle("/bin/ls", "ls", "-l", (char*)NULL, envp);
    } else if (strcmp(which, "execlp") == 0) {
        execlp("ls", "ls", "-l", (char*)NULL);
    } else if (strcmp(which, "execv") == 0) {
        char *argv[] = { (char*)"ls", (char*)"-l", NULL };
        execv("/bin/ls", argv);
    } else if (strcmp(which, "execvp") == 0) {
        char *argv[] = { (char*)"ls", (char*)"-l", NULL };
        execvp("ls", argv);
    } else if (strcmp(which, "execvpe") == 0) {
        #ifdef __GLIBC__
        char *argv[] = { (char*)"ls", (char*)"-l", NULL };
        char *envp[] = { (char*)"LC_ALL=C", NULL };
        execvpe("ls", argv, envp);
        #else
        fprintf(stderr, "execvpe not available on this platform\n");
        #endif
    } else {
        fprintf(stderr, "unknown variant: %s\n", which);
        _exit(2);
    }
    perror(which);
    _exit(1);
}

int main(int argc, char **argv) {
    const char *which = (argc > 1) ? argv[1] : "execvp";
    pid_t rc = fork();
    if (rc < 0) { perror("fork"); exit(1); }
    if (rc == 0) {
        run_variant(which);
    }
    return 0;
}
