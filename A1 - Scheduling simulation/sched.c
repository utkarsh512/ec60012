/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for scheduling utilities
 */

#include "sched.h"
#include "task.h"
#include "list.h"
#include "logging.h"
#include <stdlib.h>

/**
 * @brief Create an array of list objects for simulation
 * 
 * @return struct list** [dynamic array of N_PRIORITY lists]
 */
struct list **create_list_array()
{
    /* Create unique list for each priority level */
    struct list **list_array = (struct list **) malloc(sizeof(struct list *) * N_PRIORITY);
    for (int i = 0; i < N_PRIORITY; i++) {
        list_array[i] = create_list(i + 1);
    }
    return list_array;
}

/**
 * @brief Delete array of list objects after simulation
 * 
 * @param list_array array of list objects
 */
void delete_list_array(struct list **list_array)
{
    if (list_array == NULL) {
        LOG_FATAL("Attempt to delete null list array!\n");
    }
    for (int i = 0; i < N_PRIORITY; i++) {
        delete_list(list_array[i]);
    }
    free(list_array);
}

/**
 * @brief Create required number of jobs and add them to their respective lists
 * 
 * @param list_array array of list objects
 */
void create_jobs(struct list **list_array) 
{
    int t = 0, n_jobs = 0, dice_roll;
    LOG_DEBUG("Creating %d jobs...\n", N_JOBS);

    while (n_jobs < N_JOBS) {
        dice_roll = rand() % 6;
        if (!dice_roll) {
            struct task *task = create_task(n_jobs++, t);
            add_to_list(list_array[task->prio - 1], task);
        }
        t++;
    }
    LOG_SUCCESS("%d jobs created!\n", N_JOBS);

    for (int i = 0; i < N_PRIORITY; i++) 
        print_list(list_array[i]);
}