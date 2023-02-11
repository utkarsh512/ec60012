#
# EC60012 - Advanced Operating Systems Design
# Assignment 2 - Barber Shop Problem
# 
# Author: Utkarsh Patel (18EC35034)
#

# top-level rule to create the program.
all: barber_shop

# compiling the source file.
barber_shop.o: barber_shop.c
	gcc -g -Wall -c barber_shop.c

# linking the program.
barber_shop: barber_shop.o
	gcc -g barber_shop.o -o barber_shop -lpthread -lrt

# cleaning everything that can be automatically recreated with "make".
clean:
	/bin/rm -f barber_shop barber_shop.o