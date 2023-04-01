/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 3 - Maekawa's Algorithm
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for generating request sets for Maekawa algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "request_sets.h"
#include "projective_plane.h"
#include "matching.h"

static int is_prime[MAXN];
static int next_prime[MAXN];


/**
 * @brief Fill the `is_prime` and `next_prime` arrays using sieve of Eratosthenes
 * 
 */
void sieve_of_eratosthenes() {
    for (int i = 0; i < MAXN; i++) {
        is_prime[i] = 1;
    }
    for (int i = 2; i * i < MAXN; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    int cur_prime = -1;
    for (int i = MAXN - 1; i >= 0; i--) {
        if (is_prime[i]) {
            cur_prime = i;
        }
        next_prime[i] = cur_prime;
    }
}


/**
 * @brief Generate request set for Maekawa's algorithm
 * 
 * @details We always generate a projective plane of prime order, hence some 
 * extreneous request sets are also generated. We must preprocess them to 
 * exclude extra request sets and replace out-of-domain nodes with the nodes
 * in the domain
 * 
 * @param n_sites number of sites in Maekawa's algorithm
 * @param count_ptr pointer to number of request sets generated
 * @param order_ptr pointer to number of nodes in each request set
 * @return request sets
 */
int **generate_request_sets(int n_sites, int *count_ptr, int *order_ptr) {
    int order = 0;
    while (((order + 1) * order + 1) < n_sites) {
        order++;
    }
    assert(order < MAXN);
    order = next_prime[order];
    *order_ptr = order;
    *count_ptr = order * (order + 1) + 1;
    return generate_projective_plane(order);
}


/**
 * @brief Print the request sets for given number of sites
 * 
 * @param n_sites number of sites in Maekawa's algorithm
 */
void print_request_sets(int n_sites) {
    /* Generate request sets */
    int count, order;
    int **request_sets = generate_request_sets(n_sites, &count, &order);

    /* Each pair of generated request sets must have one and only one node
     * in commom
     */
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            int common = 0;
            for (int k = 0; k <= order; k++) {
                for (int p = 0; p <= order; p++) {
                    if (request_sets[i][k] == request_sets[j][p]) {
                        common++;
                        break;
                    }
                }
            }
            /* Only one node must be common */
            assert(common == 1);
        }
    }

    /* Create a graph for bipartite matching */
    int **graph = (int **) malloc(sizeof(int *) * count);
    for (int i = 0; i < count; i++) {
        graph[i] = (int *) malloc(sizeof(int) * count);
        for (int j = 0; j < count; j++) {
            graph[i][j] = 0;
        }
    }
    int match[count];
    memset(match, -1, sizeof(match));
    for (int i = 0; i < count; i++) {
        for (int j = 0; j <= order; j++) {
            int site = request_sets[i][j];
            graph[site][i] = 1;
        }
    }

    /* Perform bipartite matching */
    int n_matches = bipartite_matching(graph, count, count, match);
    assert(n_matches == count);

    /* Wrap around out-of-domain nodes */
    for (int i = 0; i < count; i++) {
        for (int j = 0; j <= order; j++) {
            if (request_sets[i][j] >= n_sites) {
                request_sets[i][j] %= n_sites;
            }
        }
    }

    /* Each request set to each in-domain nodes */
    int assign[n_sites];
    memset(assign, -1, sizeof(assign));
    for (int i = 0; i < count; i++) {
        if (match[i] < n_sites) {
            assign[match[i]] = i;
        }
    }

    for (int i = 0; i < n_sites; i++) {
        printf("site %5d : ", i + 1);
        assert(~assign[i]);

        /**
         * Due to wraping around of out-of-domain nodes, some duplicates might
         * be present in the modified request sets. We use a buffer as a lookup
         * for duplicates.
         */
        int buffer[order + 1];
        int pos = 0;
        for (int j = 0; j <= order; j++) {
            int exists = 0;
            for (int k = 0; k < pos; k++) {
                if (buffer[k] == request_sets[assign[i]][j]) {
                    exists = 1;
                    break;
                }
            }
            if (exists) {
                continue;
            }
            printf("%5d, ", request_sets[assign[i]][j] + 1);
            buffer[pos++] = request_sets[assign[i]][j];
        }
        printf("\n");
    }

    for (int i = 0; i < count; i++) {
        free(request_sets[i]);
        free(graph[i]);
    }
    free(request_sets);
    free(graph);
}