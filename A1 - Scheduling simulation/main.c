/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Driver code
 */

#include "srtf.h"
#include "rr.h"
#include "sched.h"
#include "task.h"
#include "list.h"
#include "logging.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>


/* Driver code */
int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        LOG_FATAL("Incorrect command! Use: \n"
                  "$ %s srtf\n"
                  "$ %s srtf_prio\n"
                  "$ %s rr\n"
                  "$ %s rr_prio\n"
                  , argv[0], argv[0], argv[0], argv[0]);
    }
    srand(time(NULL));
    if (strcmp(argv[1], "srtf_prio") == 0) {
        simulate_srtf_prio();
    }
    else if (strcmp(argv[1], "srtf") == 0) {
        simulate_srtf();
    }
    else if (strcmp(argv[1], "rr_prio") == 0) {
        simulate_rr_prio();
    }
    else if (strcmp(argv[1], "rr") == 0) {
        simulate_rr();
    }
    else {
        LOG_FATAL("Incorrect command! Use: \n"
                  "$ %s srtf\n"
                  "$ %s srtf_prio\n"
                  "$ %s rr\n"
                  "$ %s rr_prio\n"
                  , argv[0], argv[0], argv[0], argv[0]);
    }
    return 0;
}