/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 3 - Maekawa's Algorithm
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Interface for generating request sets for Maekawa algorithm
 */

#ifndef REQUEST_SETS_H
#define REQUEST_SETS_H

#define MAXN 1000000

void sieve_of_eratosthenes();
void print_request_sets(int n_sites);

#endif // REQUEST_SETS_H