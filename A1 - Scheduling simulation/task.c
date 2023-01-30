/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for task object
 */

#include <stdlib.h>
#include "task.h"
#include "logging.h"

/**
 * @brief Create a task object
 * 
 * @details Burst time and priority are chosen randomly
 * 
 * @param tid unique task id
 * @param arrival_time arrival time for the task
 * 
 * @return struct task* 
 */
struct task *create_task(int tid, int arrival_time) 
{
    struct task *task = (struct task *) malloc(sizeof(struct task));
    task->tid   = tid;
    task->atime = arrival_time;
    task->btime = BURST_TIME_MIN + rand() % (BURST_TIME_MAX - BURST_TIME_MIN);
    task->rtime = task->btime;
    task->prio  = rand() % N_PRIORITY + 1;
    task->sched = -1;
    LOG_SUCCESS("task::create_task\n\t");
    TASK_DEBUG(task);
    return task;
}

/**
 * @brief Delete a task object
 * 
 * @param task task object
 */
void delete_task(struct task *task) 
{
    if (task == NULL) {
        LOG_FATAL("task::delete_task: Attempt to deallocate a null pointer!\n");
    }
    if (task->rtime != 0) {
        LOG_FATAL("task::delete_task: Task not finished yet!\n");
    }
    LOG_DEBUG("task::delete_task\n\t");
    TASK_DEBUG(task);
    free(task);
}