CC:=gcc
CFLAGS:=-Wall -Wextra -O2

PROGS:=q1_fork_var q2_open_fork q3_child_first_no_wait q4_exec_variants q5_wait q6_waitpid q7_close_stdout

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

run: all
	@echo "---- Q1 ----"; ./q1_fork_var
	@echo "---- Q2 ----"; ./q2_open_fork; head -n 20 q2_output.txt || true
	@echo "---- Q3 ----"; ./q3_child_first_no_wait
	@echo "---- Q4 ----"; ./q4_exec_variants execvp
	@echo "---- Q5 ----"; ./q5_wait
	@echo "---- Q6 ----"; ./q6_waitpid
	@echo "---- Q7 ----"; ./q7_close_stdout; cat q7_child.out 2>/dev/null || true

clean:
	rm -f $(PROGS) q2_output.txt q7_child.out
