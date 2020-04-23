#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <sys/types.h>

typedef struct queue{
	int remain_time;
	double priority;
	int policy;
	int available_time;
	pid_t pid;
	char name[16];
	struct queue* next;
} Queue; 

// Function to Create A New Queue 
Queue *newQueue(const int remain_time, const double priority, const int policy, const pid_t pid, const char *name);

// Function to Pop a block
Queue *pop(Queue **head);

// Function to push according to priority 
void push(Queue **head, const int remain_time, const double priority, const int policy, const pid_t pid, const char *name);

// Function to check is list is empty 
int isEmpty(Queue **head);

// Function to check top process priority
double top_priority(Queue **head);

#endif
