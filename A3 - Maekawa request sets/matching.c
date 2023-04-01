/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 3 - Maekawa's Algorithm
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for bipartite matching
 */

#include <string.h>

#include "matching.h"

/**
 * @brief DFS based recursive function that returns true if a matching for vertex 
 * `u` is possible
 * 
 * @param graph adjacency matrix representation of the graph
 * @param M number of rows (applicants)
 * @param N number of columns (jobs)
 * @param u current vertex for which matching is checked
 * @param seen array to keep track of which jobs have already been visited
 * @param match array to keep track of the applicants assigned to jobs
 * @return `1` if matching is possible, else `0`
 */
int bipartite_matching_vertex(int **graph, int M, int N, int u, int *seen, int *match) {
    /* Try every job */
    for (int v = 0; v < N; v++) {
        /* If applicant `u` is interested in job `v` and `v` is not seen yet*/
        if (graph[u][v] == 1 && seen[v] == 0) {
            /* Mark job `v` as seen */
            seen[v] = 1;

            /**
             * If job `v` is not assigned to an applicant OR previously assigned
             * applicant for job `v` (which is `match[v]`) has an alternate job available.
             * Since `v` is marked as visited in the above line, `match[v]` in the 
             * following recursive call will not get job `v` again
             */
            if (match[v] < 0 || bipartite_matching_vertex(graph, M, N, match[v], seen, match)) {
                match[v] = u;
                return 1;
            }
        }
    }
    
    return 0;
}


/**
 * @brief Returns maximum number of matching from applicants to job
 * 
 * @param graph adjacency matrix representation of the graph
 * @param M number of rows (applicants)
 * @param N number of columns (jobs)
 * @param match array to keep track of the applicants assigned to jobs
 * @return maximum number of applicants which can be matched with the jobs
 */
int bipartite_matching(int **graph, int M, int N, int *match) {
    for (int i = 0; i < N; i++) {
        match[i] = -1; /* Job `i` not assigned to anyone initially */
    }
    int result = 0; /* Number of applicants matched */
    for (int u = 0; u < M; u++) {
        /* Mark all jobs as not seen for the next applicant */
        int seen[N];
        memset(seen, 0, sizeof(seen));

        /* Find if applicant `u` can get any job */
        if (bipartite_matching_vertex(graph, M, N, u, seen, match)) {
            result++;
        }
    }

    return result;
}