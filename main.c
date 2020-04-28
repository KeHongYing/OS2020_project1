#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "scheduler.h"

int main()
{
	char schedule_policy[8];
	int nproc;
	Process *proc;

	scanf("%s", schedule_policy);
	scanf("%d", &nproc);
	proc = (Process *)malloc(sizeof(Process) * nproc);

	for(int i = 0; i < nproc; i ++)
		scanf("%s%d%d", proc[i].name, &proc[i].ready_time, &proc[i].exec_time);

	int policy = check_policy(schedule_policy);
	if(policy < 0)
		err_sys("invalid policy\n");

	scheduling(proc, nproc, policy);

	return 0;
}
