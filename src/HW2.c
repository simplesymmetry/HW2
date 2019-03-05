/**
 ============================================================================
 Name        : HW2.c
 Author      : Therese Smith
 Student     : Tom Graham
 Version     : 0.2.0
 Copyright   : Copyright 2019
 Description : This is a C program used to play Jon Conway's Game of Life.
 This program accepts multiple arguments to run a game, and will run the test
 suite by  default.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tests.h"
#include "production.h"

/**
 * This is the main function used to call the actual test function and then
 * call the production function to begin the program.
 *
 * @param argc The count of variables passed at the command line.
 * @param argv The ptr to array where the arguments passed are.
 * @return 0 on sucess
 */
int main(int argc, char* argv[])
{
	bool ok=false;
	if(tests())
	{
		ok=production(argc, argv);
		if (ok)
		{
			puts("Game of life seems to have worked.");
		}
		else if (argc > 1 && !ok)
			//This is to avoid the message when no arguments as I've set my own message.
		{
			puts("Game of life seems not to have worked.");
		}
	}
	else
	{
		puts("Something went wrong in the tests.");
	}
	return EXIT_SUCCESS;
}
