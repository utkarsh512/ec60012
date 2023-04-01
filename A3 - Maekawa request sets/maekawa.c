/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 3 - Maekawa's Algorithm
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Driver code
 */

#include <stdio.h>

#include "request_sets.h"

int main() {
    sieve_of_eratosthenes();
    while (1) {
        int n;
        printf("Enter N: ");
        scanf("%d", &n);
        print_request_sets(n);
        printf("\n");
    }
}