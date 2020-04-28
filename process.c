#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include "process.h"

#define GET_TIME 334
#define PRINTK 335

void err_sys(const char *x)
{
	perror(x);
	exit(0);
}

void assign(const pid_t pid, const int core)
{
	if(core > 1)
		err_sys("Core error");
	
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);
	
	if(sched_setaffinity(pid, sizeof(mask), &mask) < 0)
		err_sys("scheduler set affinity error");

	return;
}

pid_t execute(Process proc)
{
	pid_t pid = fork();

	if(pid < 0)
		err_sys("fork error");

	if(pid == 0){
		unsigned long start_sec, start_nsec, end_sec, end_nsec;
		char dmesg[512];

		struct sched_param parm;
		while(1){
			if(sched_getparam(getpid(), &parm) < 0)
				err_sys("get parm error");

			if(parm.sched_priority == 99)
				break;
		}

		syscall(GET_TIME, &start_sec, &start_nsec);

		UNIT_TIME(proc.exec_time);

		syscall(GET_TIME, &end_sec, &end_nsec);
		sprintf(dmesg, "[Project1] %d %lu.%09lu %lu.%09lu", getpid(), start_sec, start_nsec, end_sec, end_nsec);
		syscall(PRINTK, dmesg);

		exit(0);
	}
	block(pid);
	return pid;
}

void block(const pid_t pid)
{
	struct sched_param parm;
	parm.sched_priority = 1;

	if(sched_setscheduler(pid, SCHED_FIFO, &parm) < 0)
		err_sys("set scheduler error");

	assign(pid, PARENT_CPU);	
	return;
}

void wakeup(const pid_t pid)
{
	assign(pid, CHILD_CPU);
	
	struct sched_param parm;
	parm.sched_priority = 99;

	if(sched_setscheduler(pid, SCHED_FIFO, &parm) < 0)
		err_sys("set scheduler error");
	
	return;	
}

void UNIT_TIME(const int N)
{
	for(int n = 0; n < N; n ++)
		for(volatile unsigned i = 0; i < 1000000UL; i ++);
}
