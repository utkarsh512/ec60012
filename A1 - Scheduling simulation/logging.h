/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 1 - CPU Scheduling
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Interface for logging
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdlib.h>

#define COL_FATAL     "\x1B[31m"  /* red terminal */
#define COL_SUCCESS   "\x1B[32m"  /* green terminal */
#define COL_DEBUG     "\x1B[36m"  /* cyan terminal */
#define COL_RESET     "\x1B[0m"

#ifdef DEBUG
#define LOG_DEBUG(...)    \
    printf(COL_DEBUG);    \
    printf( __VA_ARGS__); \
    printf(COL_RESET)

#define LOG_SUCCESS(...) \
    printf(COL_SUCCESS); \
    printf(__VA_ARGS__); \
    printf(COL_RESET)

#else
#define LOG_DEBUG(...)
#define LOG_SUCCESS(...)
#endif /* DEBUG */

#define LOG_INFO(...)    \
    printf(COL_DEBUG);    \
    printf( __VA_ARGS__); \
    printf(COL_RESET)

#define LOG_FATAL(...)    \
    printf(COL_FATAL);    \
    printf(__VA_ARGS__);  \ 
    printf(COL_RESET);    \
    exit(EXIT_FAILURE)

#endif /* LOGGING_H */
