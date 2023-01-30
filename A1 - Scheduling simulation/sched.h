/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Interface for scheduling utilities
 */

#ifndef SCHED_H
#define SCHED_H

#include "list.h"
#include "task.h"
#include "logging.h"
#include <stdlib.h>

#define N_JOBS 1000
#define TIME_QUANTUM 10

#define MIN(a, b) (a) < (b) ? (a) : (b)

struct list **create_list_array();
void        delete_list_array(struct list **);
void        create_jobs(struct list **);

#endif /* SCHED_H */