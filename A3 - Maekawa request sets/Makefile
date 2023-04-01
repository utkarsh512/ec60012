#
# EC60012 - Advanced Operating Systems Design
# Assignment 3 - Maekawa's Algorithm
# 
# Author: Utkarsh Patel (18EC35034)
#

obj_files = maekawa.o projective_plane.o request_sets.o matching.o

all: maekawa

matching.o: matching.c
	gcc -g -Wall -c $^ -o $@

projective_plane.o: projective_plane.c
	gcc -g -Wall -c $^ -o $@

request_sets.o: request_sets.c
	gcc -g -Wall -c $^ -o $@

maekawa.o: maekawa.c
	gcc -g -Wall -c $^ -o $@

maekawa: $(obj_files)
	gcc -g -Wall $^ -o $@

clean:
	rm -f maekawa $(obj_files)