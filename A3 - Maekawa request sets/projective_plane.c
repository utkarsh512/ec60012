/**
 * EC60012 - Advanced Operating Systems Design
 * Assignment 3 - Maekawa's Algorithm
 * 
 * Author: Utkarsh Patel (18EC35034)
 * 
 * Implementation for generating a projective plane of a prime order
 */

#include <stdlib.h>

#include "projective_plane.h"

/**
 * @brief Generate a projective plane of prime `order`
 * 
 * @details In a projective plane, there are no parallel lines. A projective 
 * plane of order `n` has `n**2 + n + 1` points and lines, with `n + 1` points 
 * on each line, and `n + 1` lines on each point.
 * Nice reading on projective planes:
 * http://www.mathpuzzle.com/MAA/47-Fano/mathgames_05_30_06.html
 * 
 * @param order order of the projective plane, it must be a prime number
 */
int **generate_projective_plane(int order) {
    int size = order * (order + 1) + 1;
    int **projective_plane = (int **) malloc(sizeof(int *) * size);
    int idx = 0;

    for (int i = 0; i < order; i++) {
        projective_plane[idx] = (int *) malloc(sizeof(int) * (order + 1));
        for (int j = 0; j < order; j++) {
            projective_plane[idx][j] = i * order + j;
        }
        projective_plane[idx][order] = order * order;
        idx++;
    }

    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            projective_plane[idx] = (int *) malloc(sizeof(int) * (order + 1));
            for (int k = 0; k < order; k++) {
                projective_plane[idx][k] = k * order + (j + i * k) % order;
            }
            projective_plane[idx][order] = order * order + 1 + i;
            idx++;
        }
    }

    projective_plane[idx] = (int *) malloc(sizeof(int) * (order + 1));
    for (int i = 0; i <= order; i++) {
        projective_plane[idx][i] = order * order + i;
    }

    return projective_plane;
}