#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <sys/types.h>

#define PARENT_CPU 0
#define CHILD_CPU 1

typedef struct{
	char name[32];
	int ready_time, exec_time;
	pid_t pid;
} Process;

// Error handler
void err_sys(const char *x);

// Assgin a CPU for specific process
void assign(const pid_t pid, const int core);

// Start to run the process
pid_t execute(Process proc);

// Block a proccess
void block(const pid_t pid);

// Wakeup a process
void wakeup(const pid_t pid);

void UNIT_TIME(const int N);

#endif
