/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Interface for task object
 */

#ifndef TASK_H
#define TASK_H

#include "logging.h"

#define BURST_TIME_MIN 5    /* minimum burst time of a task */
#define BURST_TIME_MAX 100  /* maximum burst time of a task */
#define N_PRIORITY 3        /* number of priority levels */


struct task {
    int tid;    /* task unique id */
    int atime;  /* arrival time   */
    int btime;  /* burst time     */
    int rtime;  /* time remianing */
    int prio;   /* task priority  */
    int sched;  /* time it was scheduled by RR scheduler */
};

#define TASK_DEBUG(task) \
    LOG_DEBUG("task(tid=%d, atime=%d, btime=%d, rtime=%d, prio=%d)\n", \
    (task)->tid, (task)->atime, (task)->btime, (task)->rtime, (task)->prio)

struct task *create_task(int, int);
void        delete_task (struct task *);     

#endif /* TASK_H */