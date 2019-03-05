/**
 * tests.c
 * This is a file for the tests.c. The functions have comments
 * explaining what they do in the actual
 *
 *  Created on: January 31, 2019
 *      Author: Therese Smith
 *      Student: Tom Graham
 */

#include <stdbool.h>
#include "tests.h"
#include "production.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * This function is used to test the rest of the program.
 * It simply breaks up the operations using boolean returns.
 *
 * @return A boolean variable results, true if success false otherwise
 */
bool tests(void)
{
	bool results=false;
	puts("During tests");
	bool ok1 = testReadInput();
	if(ok1)puts("Found and read the test file.");
	bool ok2 = testMakeArrays();
	if(ok2)puts("Was able to allocate the arrays ok.");
	bool ok3 = testPlayOne();
	if(ok3)puts("playOne is ok.");
	bool ok4 = testSameContent();
	if(ok4)puts("SameContent is ok.");
	bool ok5 = testAnyX();
	if(ok5)puts("testAnyX is ok.");
	puts("end of tests");
	results = ok1 && ok2 && ok3 && ok4 && ok5;
	if (results)
		printf("Tests were successful!\n");
	return results;
}

/**
 * This function returns a boolean T/F after testing the read input.
 *
 * @return True if success and false otherwise.
 */
bool testReadInput(void)
{
	//First we create the multiple boolean variables to use to help control the flow.
	bool results = false;
	bool ok1 = false;
	bool ok2 = false;
	bool ok3 = false;

	//First we create the fp, and write the file to read later.
	FILE* fp;
	fp = fopen("/tmp/LifeInput.txt", "w");

	//If the file is found
	if (fp != false)
	{
		//We will write the lines to the file.
		int w1 = fprintf(fp, "oxo\n");
		int w2 = fprintf(fp, "xox\n");
		int w3 = fprintf(fp, "xox\n");
		int w4 = fprintf(fp, "oxo\n");

		//Then check if they are all equal.
		if ((w1 == w2) && (w2 == w3) && (w3 == w4) && (w4 == 4))
		{
			ok1 = true;
		}
		fclose(fp);
	}

	//Now we try to read it
	fp = fopen("/tmp/LifeInput.txt", "r");

	//If the file opens then
	if (fp != false)
	{
		//set ok2 to true
		ok2 = true;

		//We will use this as a char buffer set to the chars we want.
		char oRow[4];
		int count =  fscanf(fp, "%s", oRow);

		//If they match we succeed.
		if(0==strncmp(oRow, "oxo", 4))
		{
			ok3 = true;
		}
		fscanf(fp, "%s", oRow);
		if(0==strncmp(oRow, "xox", 4))
		{
			ok3 = true;
		}
		fscanf(fp, "%s", oRow);
		if(0==strncmp(oRow, "xox", 4))
		{
			ok3 = true;
		}
		fscanf(fp, "%s", oRow);
		if(0==strncmp(oRow, "oxo", 4))
		{
			ok3 = true;
		}
	}
	results = ok1 && ok2 && ok3;
	return results;
}

/**
 * This function is used to make the actual arrays.
 *
 * @return True on success and false otherwise.
 */
bool testMakeArrays(void)
{
	//The initial booleans to be used as control statements.
	bool results = false;
	bool ok1 = false;

	//The max row and col are 4.
	int nRows = 4;
	int nCols = 4;

	//The arrays on the stack like the hw asked.
	char boardBefore[4][4]={
			{'o','x','o','\0'},
			{'x','o','x','\0'},
			{'x','o','x','\0'},
			{'o','x','o','\0'}
	};

	//The arrays on stack like the hw asked again.
	char boardAfter[nRows][nCols];

	//Then looping through the indices and make sure they are equal.
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			boardAfter[row][col]=boardBefore[row][col];
		}
	}
	ok1 = true;

	//Again loop through the indcies and make sure they are equal.
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			if (boardAfter[row][col]!=boardBefore[row][col])
			{
				ok1=false;
			}
		}
	}

	results = ok1;
	return results;
}

/*
 * This function is used to test the play one function and return a boolean T/F.
 *
 * @return True on sucess and false otherwise.
 */
bool testPlayOne(void)
{
	//Setup the inital boolean variables.
	bool results = false;
	bool ok1 = false;
	bool ok2 = false;

	//Declare and initialize the total rows and cols.
	int nRows = 4;
	int nCols = 3;

	//We will make the arrays on the stack like the hw asked.
	char boardBefore[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};
	//We will make the arrays on the stack like the hw asked.
	char correctBoardAfter[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};
	//We will make the arrays on the stack like the hw asked.
	char boardAfter[4][3];
	//Then we will call the playone function to actually play one.
	PlayOne(nRows, nCols, (char*)boardBefore, (char*)boardAfter);
	ok1 = true; //no errors found yet
	//We loop through the indices checking if the boards are equal.
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			if(boardAfter[row][col]!=correctBoardAfter[row][col])
			{//error found
				ok1 = false;
			}
		}
	}
	results = ok1;
	return results;
}

/**
 * This is a boolean function used to test the sameContent function of the production.c file.
 *
 * @return True if the tests succeed, and false otherwise.
 */
bool testSameContent(void){

	//The general switch for pass/fail.
	bool same = false;
	//The first test boolean.
	bool ok1 = false;
	//The second test boolean.
	bool ok2 = false;

	//The arrays are all hardcoded for simplicity.
	char boardBefore[4][3]={
			{'o','x','o'},
			{'x','o','x'},
			{'x','o','x'},
			{'o','x','o'}
	};
	char boardAfter[4][3]={
			{'o','o','o'},
			{'o','o','o'},
			{'o','o','o'},
			{'o','o','o'}
	};
	char boardBefore2[3][3]={
			{'o','o','o'},
			{'o','o','o'},
			{'o','o','o'},
	};
	char boardAfter2[3][3]={
			{'o','o','o'},
			{'o','o','o'},
			{'o','o','o'},
	};

//	char * ptrBoardAfter = &boardAfter[0][0];
//	char * ptrBoardBefore = &boardBefore[0][0];
//	char * ptrBoardAfter2 = &boardAfter2[0][0];
//	char * ptrBoardBefore2 = &boardBefore2[0][0];



	//sameContent call, they aren't the same
	if (!sameContent((char*)boardBefore, (char*)boardAfter, 4, 3)){
		ok1 = true;
	}

	//sameContent call, they are the same
	if (sameContent((char*)boardBefore2, (char*) boardAfter2, 3, 3)){
		ok2 = true;
	}

	//both must be true for function to be considered working.
	same = ok1 && ok2;

	return same;
}

/**
 * This boolean test is for the function AnyX.
 *
 * @return True if there are x's and false otherwise.
 */
bool testAnyX(void){

	//Using a boolean switch to test
	bool result = false;
	//The first test boolean.
	bool ok1 = false;
	//The second test boolean.
	bool ok2 = false;

	//A game board that contains no x's
	char boardNoX[3][3]={
			{'o','o','o'},
			{'o','o','o'},
			{'o','o','o'},
	};

	//A game board that contains x's
	char boardHasX[3][3]={
			{'o','o','o'},
			{'o','x','o'},
			{'o','o','o'},
	};

	//The pointers associated with the boards.
	char * ptrBoardNoX = &boardNoX[0][0];
	char * ptrBoardHasX = &boardHasX[0][0];

	//There is no x, so result is true if it rets 0 ! it to get 1.
	if(!anyX(ptrBoardNoX, 3, 3)){
		ok1 = true;
	}

	//There is an x, so result is only true if call is true.
	if(anyX(ptrBoardHasX, 3, 3)){
		ok2 = true;
	}

	result = ok1 && ok2;
	return result;
}

