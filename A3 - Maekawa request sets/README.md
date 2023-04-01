# Maekawa's algorithm: Generating request sets

### EC60012 - Advanced Operating Systems Design - Assignment 3

#### Utkarsh Patel

## Maekawa's algorithm

Maekawa's algorithm is an algorithm for mutual exclusion on a distributed system. The basis of this algorithm is a quorum like approach where any one site needs only to seek permissions from a subset of other sites.

Quorum set (or request set) <img src="https://latex.codecogs.com/svg.latex?R_i" /> for each site <img src="https://latex.codecogs.com/svg.latex?S_i" /> must abide by the following rules:
- <img src="https://latex.codecogs.com/svg.latex?\forall%20i%20\forall%20j,%20R_i%20\cap%20R_j%20=%20\O" />
- <img src="https://latex.codecogs.com/svg.latex?\forall%20i,%20S_i%20\in%20R_i" />
- <img src="https://latex.codecogs.com/svg.latex?\forall%20i,%20|%20R_i%20|%20=%20K" />
- Site <img src="https://latex.codecogs.com/svg.latex?S_i" /> is contained in exactly <img src="https://latex.codecogs.com/svg.latex?K" /> request sets

Therefore, <img src="https://latex.codecogs.com/svg.latex?\forall%20i,%20|%20R_i%20|%20\geq%20\sqrt{N%20-%201}" />

## Generating request sets

If the number of site can be represented as <img src="https://latex.codecogs.com/svg.latex?N%20=%20K(K%20-%201)%20+%201" />, then the problem translates to generating a **projective plane** of order <img src="https://latex.codecogs.com/svg.latex?K-1"/>. Solution exist if <img src="https://latex.codecogs.com/svg.latex?K-1"/> is a power of prime, <img src="https://latex.codecogs.com/svg.latex?p^m"/>, for some prime <img src="https://latex.codecogs.com/svg.latex?p"/>. For other cases, we can relax the last two conditions to create degenerate request sets.

## Build and run
```shell
$ cd maekawa
$ make
$ ./maekawa
```

## References
- [Math Games: The Fano Plane](http://www.mathpuzzle.com/MAA/47-Fano/mathgames_05_30_06.html)
