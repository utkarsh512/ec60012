/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for linked-list data structure for scheduling
 */

#include "list.h"
#include "task.h"
#include "logging.h"
#include <stdlib.h>


/**
 * @brief Wrap a task object inside a list node object
 * 
 * @param task task object to wrap
 * 
 * @return struct list_node* 
 */
struct list_node *wrap_task_in_list_node(struct task *task)
{
    if (task == NULL) {
        LOG_FATAL("list::wrap_task_in_list_node: Cannot wrap a null task object\n");
    }
    struct list_node *list_node = (struct list_node *) \
        malloc(sizeof(struct list_node));
    list_node->task = task;
    list_node->next = NULL;
    return list_node;
}

/**
 * @brief Delete a list node
 * 
 * @param list_node list node object
 * 
 * @note This doesn't delete the wrapped task object inside the list node object
 */
void delete_list_node(struct list_node *list_node) 
{
    if (list_node == NULL) {
        LOG_FATAL("list::delete_list_node: Attempt to deallocate a null pointer!\n");
    }
    free(list_node);
}

/**
 * @brief Create a list object for a given priority level
 * 
 * @param prio priority level
 * @return struct list* 
 */
struct list *create_list(int prio) 
{
    struct list *list = (struct list *) malloc(sizeof(list));
    list->prio = prio;
    list->head = NULL;
    LOG_SUCCESS("list::create_list\n");
    print_list(list);
    return list;
}

/**
 * @brief Print tasks contained in the list object
 * 
 * @param list list object
 */
void print_list(struct list *list) 
{
    if (list == NULL) {
        LOG_FATAL("list::print_list: List object not initialized!\n");
    }
    LOG_DEBUG("List of tasks for priority-level %d\n", list->prio);
    if (list->head == NULL) { /* Empty list object */
        LOG_DEBUG("\t\t<EMPTY>\n");
        return;
    }
    struct list_node *list_node = list->head;
    while (list_node != NULL) {
        LOG_DEBUG("\t\t");
        TASK_DEBUG(list_node->task);
        list_node = list_node->next;
    }
}

/**
 * @brief Delete list object
 * 
 * @param list list object
 */
void delete_list(struct list *list)
{
    if (list == NULL) {
        LOG_FATAL("list::delete_list: Attempt to deallocate a null pointer!\n");
    }
    struct list_node *list_node = list->head, *temp_node = NULL;
    while (list_node != NULL) {
        temp_node = list_node;
        list_node = list_node->next;
        delete_task(temp_node->task);
        delete_list_node(temp_node);
    }
    free(list);
    LOG_SUCCESS("list::delete_list\n");
}

/**
 * @brief Add a task to the list
 * 
 * @param list list object
 * @param task task object
 */
void add_to_list(struct list *list, struct task *task)
{
    if (list == NULL) {
        LOG_FATAL("list::print_list: List object not initialized!\n");
    }
    if (task == NULL) {
        LOG_FATAL("list::add_to_list: Task object not initialized!\n");
    }
    if (list->prio != task->prio) {
        LOG_FATAL("list::add_to_list: Cannot add task for priority level %d to "
                  "the list of priority level %d!\n", task->prio, list->prio);
    }
    
    struct list_node *list_node = wrap_task_in_list_node(task);
    list_node->next = list->head;
    list->head = list_node;
    LOG_SUCCESS("list::add_to_list\n\t");
    TASK_DEBUG(task);
}

/**
 * @brief Remove a task from the list
 * 
 * @param list list object
 * @param task task object
 */
void remove_from_list(struct list *list, struct task *task)
{
    if (list == NULL) {
        LOG_FATAL("list::remove_from_list: List object not initialized!\n");
    }
    if (task == NULL) {
        LOG_FATAL("list::remove_from_list: Task object not initialized!\n");
    }

    struct list_node *iter = list->head, *prev;

    /* If head node itself holds the task to be deleted */
    if (iter != NULL && iter->task->tid == task->tid) {
        list->head = iter->next;
        LOG_DEBUG("list::remove_from_list: Attempting to delete task\n\t");
        TASK_DEBUG(task);
        delete_list_node(iter);
        return;
    }

    /* Find the list node for the given task */
    while (iter != NULL && iter->task->tid != task->tid) {
        prev = iter;
        iter = iter->next;
    }
    
    prev->next = iter->next;
    LOG_DEBUG("list::remove_from_list: Removing task\n\t");
    TASK_DEBUG(task);
    delete_list_node(iter);
}