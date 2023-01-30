/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Interface for linked-list data structure for scheduling
 */

#ifndef LIST_H
#define LIST_H

#include "task.h"

struct list_node {
    struct task      *task; /* task object */
    struct list_node *next;
};

struct list {
    int prio; /* priority level of task in this list */
    struct list_node *head;
};

struct list *create_list     (int);
void        print_list       (struct list *);
void        delete_list      (struct list *);
void        add_to_list      (struct list *, struct task *);
void        remove_from_list (struct list *, struct task *);

#endif /* LIST_H */