#define _GNU_SOURCE

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include "scheduler.h"
#include "process.h"
#include "priority_queue.h"

double determine_priority(const int policy, const int exec_time)
{
	if(policy == FIFO || policy == RR)
		return 0;
	else
		return 1.0 / exec_time;
}

int compare(const void *a, const void *b)
{
	return ((Process *)a) -> ready_time > ((Process *)b) -> ready_time;
}

int check_policy(const char *policy)
{
	if(strcmp(policy, "FIFO") == 0)
		return FIFO;
	else if(strcmp(policy, "RR") == 0)
		return RR;
	else if(strcmp(policy, "SJF") == 0)
		return SJF;
	else if(strcmp(policy, "PSJF") == 0)
		return PSJF;
	else
		return -1;
}

int preemtive(const double p1, const double p2)
{
	//fprintf(stderr, "p1 %f p2 %f\n", p1, p2);
	return p1 < p2;
}

void context_switch(Queue **head, Queue **running)
{
	if((*running) != NULL){
		block((*running) -> pid);
		push(head, (*running) -> remain_time, (*running) -> priority, (*running) -> policy, (*running) -> pid, (*running) -> name);
		//fprintf(stderr, "push %s\n", (*running) -> name);
		free((*running));
	}
	(*running) = pop(head);
	if((*running) != NULL)
		wakeup((*running) -> pid);

	fprintf(stderr, "switch to %s pid %d\n", (*running) -> name, (*running) -> pid);
	
	return;
}

void scheduling(Process *proc, const int nproc, const int policy)
{
	int time = 0, finish = 0;

	qsort(proc, nproc, sizeof(Process), compare);

	for(int i = 0; i < nproc; i ++)
		proc[i].pid = -1;

	assign(getpid(), PARENT_CPU);
	wakeup(getpid());

	Queue *pq = NULL;
	Queue *running = NULL;
	while(1){
		for(int i = 0; i < nproc; i ++){
			if(proc[i].ready_time == time){
				proc[i].pid = execute(proc[i]);
				//fprintf(stderr, "%s pid %d in\n", proc[i].name, proc[i].pid);

				if(pq == NULL)
					pq = newQueue(proc[i].exec_time, determine_priority(policy, proc[i].exec_time), policy, proc[i].pid, proc[i].name);
				else
					push(&pq, proc[i].exec_time, determine_priority(policy, proc[i].exec_time), policy, proc[i].pid, proc[i].name);

				//fprintf(stderr, "%s exec_time %d priority %f\n", proc[i].name, proc[i].exec_time, determine_priority(policy, proc[i].exec_time));
				
				if(policy == PSJF && running != NULL){
					if(preemtive(running -> priority, top_priority(&pq)))
						context_switch(&pq, &running);
				}
			}
		}

		if(running == NULL && pq != NULL){
			//fprintf(stderr, "choose queue\n");
			context_switch(&pq, &running);
		}
		
		UNIT_TIME(1);
		time ++;

		if(running != NULL){
			running -> available_time -= 1;
			running -> remain_time -= 1;
			if(running -> available_time == 0){
				if(running -> remain_time != 0){ //RR timeout but haven't finish
					if(pq == NULL)
						running -> available_time = (running -> remain_time > 500) ? 500 : running -> remain_time;
					else
						context_switch(&pq, &running);
				}
				else{ //process finish
					//fprintf(stderr, "%s pid %d finish\n", running -> name, running -> pid);
					waitpid(running -> pid, NULL, 0);
					printf("%s %d\n", running -> name, running -> pid);
					fflush(stdout);
					finish ++;
					running = NULL;
					
					if(finish == nproc){ //all process finish
						break;
					}
				}
			}
			else{
				running -> priority = determine_priority(policy, running -> remain_time);
			}
		}
	}
	return;
}
