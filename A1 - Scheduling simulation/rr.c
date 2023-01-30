/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for simulating round robin CPU scheduling
 */

#include "sched.h"
#include "rr.h"
#include "task.h"
#include "list.h"
#include "logging.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>


/**
 * @brief Fetch the next job to execute for SRTF scheduler
 * 
 * @param list_array array of list objects
 * @param t current time in scheduler
 * @param FLAGS '1' if we want to consider priority, otherwise '0'
 * @return struct task* 
 */
struct task *fetch_next_job_rr(struct list **list_array, int t, int FLAGS)
{
    struct task *next_job = NULL, *candidate;
    struct list_node *iter;
    if (FLAGS) {
        /* Priority level will be considered */
        for (int i = 0; i < N_PRIORITY; i++) {
            for (iter = list_array[i]->head; iter != NULL; iter = iter->next) {
                candidate = iter->task;
                if (candidate->atime > t) {
                    continue;
                }
                if (next_job == NULL ||
                    (candidate->sched < next_job->sched || \
                    (candidate->sched == next_job->sched && \
                    candidate->prio < next_job->prio))) 
                {
                    next_job = candidate;
                }
            }
        }
    }

    else {
        /* Priority level will not be considered */
        for (int i = 0; i < N_PRIORITY; i++) {
            for (iter = list_array[i]->head; iter != NULL; iter = iter->next) {
                candidate = iter->task;
                if (candidate->atime > t) {
                    continue;
                }
                if (next_job == NULL || candidate->sched < next_job->sched) 
                {
                    next_job = candidate;
                }
            }
        }
    }

    /* Delete next_job from list_array */
    if (next_job != NULL) {
        remove_from_list(list_array[next_job->prio - 1], next_job);
    }

    return next_job;
}

/**
 * @brief Utitity routine for simulating RR scheduling
 * 
 * @param FLAGS FLAGS should be '1' if we want to consider priority, otherwise
 *        priority level of tasks is ignored
 */
void rr(int FLAGS)
{
    /* Construct unique list for each priority level */
    struct list **list_array = create_list_array();
    /* Create jobs and add them to their respective lists */
    create_jobs(list_array);

    double avg_turnaround_time = 0;
    struct task *running = NULL;
    int time_quantum;

    LOG_INFO("   Clock\t\tProcess\t\tArrival Time\t\tBurst Time\t\tRemaining Time\t\tPriority\n");
    LOG_INFO("   -----\t\t-------\t\t------------\t\t----------\t\t--------------\t\t--------\n");

    for (int t = 0, n_jobs = 0; n_jobs < N_JOBS;) {
        running = fetch_next_job_rr(list_array, t, FLAGS);
        if (running == NULL) {
            /* No job available for servicing */
            t++;
            continue;
        }

        assert(running->rtime); /* Make sure the job has non-zero remaining time */
        LOG_INFO("%8d\t\t%7d\t\t%12d\t\t%10d\t\t%14d\t\t%8d\n", 
                 t, running->tid, running->atime, running->btime, 
                 running->rtime, running->prio);
        time_quantum = MIN(TIME_QUANTUM, running->rtime);
        running->rtime -= time_quantum;
        running->sched = t;
        t += time_quantum;

        if (running->rtime == 0) {
            avg_turnaround_time += t - running->atime;
            delete_task(running);
            n_jobs++;
        } else {
            add_to_list(list_array[running->prio - 1], running);
        }
    }
    delete_list_array(list_array);
    avg_turnaround_time /= N_JOBS;
    LOG_INFO("Average turnaround time: %.4f units.\n", avg_turnaround_time);
}

/**
 * @brief Simulate round robin scheduling without using priority levels
 * 
 */
void simulate_rr()
{
    /* Call `rr` with FLAGS=0 */
    rr(0);
}

/**
 * @brief Simulate round robin scheduling using priority levels
 * 
 */
void simulate_rr_prio()
{
    /* Call `rr` with FLAGS=1 */
    rr(1);
}