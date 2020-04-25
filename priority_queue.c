#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"
#include "scheduler.h"

// Function to Create A New Queue 
Queue *newQueue(const int remain_time, const double priority, const int policy, const pid_t pid, const char *name) 
{
	Queue *temp = (Queue*)malloc(sizeof(Queue));
	temp -> remain_time = remain_time;
	temp -> priority = priority;
	temp -> next = NULL;
	temp -> policy = policy;
	temp -> available_time = (policy == RR && remain_time > TIME_QUANTUM) ? TIME_QUANTUM : remain_time;
	temp -> pid = pid;
	strcpy(temp -> name, name);

	return temp;
}

// Removes the element with the 
// highest priority form the list 
Queue *pop(Queue** head) 
{
	Queue *temp = *head;
	(*head) = (*head) -> next;
	return temp;
}

// Function to push according to priority 
void push(Queue **head, const int remain_time, const double priority, const int policy, const pid_t pid, const char *name)
{
	Queue *start = (*head);

	// Create new Queue 
	Queue *temp = newQueue(remain_time, priority, policy, pid, name);

	// Special Case: The head of list has lesser 
	// priority than new node. So insert new 
	// node before head node and change head node. 
	if((*head) -> priority < priority){
		// Insert New Queue before head 
		temp -> next = *head;
		(*head) = temp;
	}
	else{
		// Traverse the list and find a 
		// position to insert new node 
		while(start -> next != NULL && start -> next -> priority >= priority)
			start = start -> next;

		// Either at the ends of the list 
		// or at required position 
		temp -> next = start -> next;
		start -> next = temp;
	}
}

// Function to check is list is empty 
int isEmpty(Queue **head) 
{
	return (*head) == NULL;
}

double top_priority(Queue **head)
{
	return (*head) -> priority;
}
