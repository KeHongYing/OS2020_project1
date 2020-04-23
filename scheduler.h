#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

#include "process.h"

#define FIFO 0
#define RR 1
#define SJF 2
#define PSJF 3
#define GET_TIME 314
#define PRINK 315
#define TIME_QUANTUM 500

// Check which policy
int check_policy(const char *policy);

// Schedule the process
void scheduling(Process *proc, const int nproc, const int policy);

#endif
