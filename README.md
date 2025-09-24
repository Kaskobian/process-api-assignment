# Using the Process API — fork(), exec(), wait()

Build:
```bash
make
```
Run small demos:
```bash
make run
```

## Q1 — fork() and variable x
After fork, child gets a copy-on-write address space. Both see initial x, but later writes are independent.
See `q1_fork_var.c`.

## Q2 — open()+fork() shared FD
Parent/child share the same open-file description, so writes interleave and share the file offset.
See `q2_open_fork.c` (generates `q2_output.txt`).

## Q3 — child prints first without wait()
Use a pipe: parent blocks on read until child signals. See `q3_child_first_no_wait.c`.

## Q4 — exec variants
Demonstrates execl/execle/execlp/execv/execvp/execvpe (if available). See `q4_exec_variants.c`.

## Q5 — wait()
In parent, wait() returns child's PID and fills status; in child, wait() fails with ECHILD. See `q5_wait.c`.

## Q6 — waitpid()
Wait for a specific child (or use WNOHANG). Useful with multiple children. See `q6_waitpid.c`.

## Q7 — close stdout in child
After closing fd 1, printf can't write to terminal; if a new file opens, it may reuse fd 1 -> output goes there.
See `q7_close_stdout.c`.
