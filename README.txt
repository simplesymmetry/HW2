 ============================================================================
 Name 		 	:	README.txt
 Student   		:	Tom Graham
 Assignment	: 	John Conway's Game of Life
 Language		:	C
 Copyright  		: 	Copyright 2019
 ============================================================================

Files Included:  
.C:	HW2.c production.c tests.c
.h:	production.h tests.h

Usage: ./HW2 NR NC gens inputfile [print] [pause]

./HW2 	- argv[0] - 	The name of the program.
NR 		- argv[1] - 	Number of rows to use for the game grid.
NC 		- argv[2] - 	Number of columns to use for the game grid.
gens  	- argv[3] - 	Number of generations to iterate through.
input	- argv[4] - 	The input file to read from.
print	- argv[5] -	The print toggle used to output each generation.
pause	- argv[6] -	The pause toggle used to pause after generation.

This program iterates through the Game of Life for a given seed board. It takes the input and
parameters NR, NC, gens: they are number of rows, number of columns and number of 
generations.

to build:
	-make (with included makefile)
	or 
	-gcc HW2.c production.c tests.c  

normal:
	-The game will run the test suite automatically. 
	--If the tests passed it will say: "Tests were successful!".

	-If you run the program with no arguments, it will print the usage message and the string
	--"Game of life seems not to have worked". This is 

testing:
	-This version of the game of course works with all trival patterns.
	-It also works with all the provided text files.

	-This verison of game of life does work with acorn!
		./HW2 168 215 5206 acorn.txt y n
	-Will produce the correct result on 5206 generations.
