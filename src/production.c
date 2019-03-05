/**
 * production.c
 * This is the the actual production part of the code, this is where what
 * is being tested is written. Also where the majority of the functions
 * are written.
 *
 *  Created on: January 31, 2019
 *      Author: Therese Smith
 *      Student: Tom Graham
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "production.h"
#include <math.h>
#include <string.h>
#include <errno.h>

/**
 * This is the boolean function to run the logistics of the program.
 * This will do basic checks on inputs from the command line.
 *
 * @param argc The number of arguments passed to the function on run.
 * @param argv The pointer to the argument array.
 * @return This will return true if production worked and false if it failed.
 */
bool production(int argc, char* argv[])
{

	//The overal results boolean variable.
	bool results = false;

	//The final boolean variable for completetion.
	bool done = false;

	//Number of rows.
	int nRows=-1;

	//Number of cols.
	int nCols = -1;

	//Number of lines on line
	int howManyLinesInFile = 0;

	//Number of generations to play.
	int gens = 0;

	//The maximum size of cols
	int maximumWidth = 0;

	//Char buffer for filename.
	char filename[100];

	//Loop to store filename, filled with '\0' on start.
	for(int i= 0; i<100; i++)
	{
		filename[i]='\0';
	}

	//Defaulting the print and pause both to no.
	char print = 'n';
	char pause = 'n';

	//If not enough args provided then the Usage will be printed.
	//./HW2 NR NC gens input [print] [pause]
	//Else if there are 7 or more args then check and get pause state.
	if(argc<5)
	{
		usage();
		done=true;
	}
	else if (argc >= 7)
	{
		pause = argv[6][0];
	}
	if (!done && (argc >= 6)) //Get print state.
	{
		print = argv[5][0];
	}

	if (argc >= 8){
		perror("Too many arguments.");
		usage();
		done = true;
		return -1;
	}

	//If not done, fill in the rest of the arguments.
	if(!done)
	{
		//Ptr for strtol call.
		char* ptr=0;
		//Get the number of rows and set to nr_l, then convert to int nRows.
		long nr_l = strtol(argv[1],&ptr,10);
		nRows = (int)nr_l;

		//If rows are less than 1, print error and done = true.
		if(nRows<1 || nRows > 250)
		{
			printf("Usage: Rows should be greater than 0 and less than 250, but received %d.\n",nRows);
			done = true;
		}

		//Ptr for strtol call #2.
		char* ptr2=0;

		//Get the number of cols, and set to nr_c, then conver to int nCols.
		long nr_c = strtol(argv[2],&ptr2,10);
		nCols = (int)nr_c;

		if(nCols<1 || nCols > 250)
		{
			printf("Usage: Cols should be greater than 0 and less than 250, but received %d.\n",nRows);
			done = true;
		}

		//Ptr for strtol call #3.
		char* ptr3=0;
		long gen = strtol(argv[3],&ptr3,10);//get the NR
		gens = (int)gen;

		//Copys the filename from the argv to the filename buffer
		strcpy(filename, argv[4]);

		//Now we read file
		FILE* fp = fopen(filename, "r");

		//If we can open the file, we're good.
		if (fp != false)
		{
			printf("\nOpened %s.\n\n",filename);

			//Buffer for the data from the file.
			//Can change to #ofCols but I think 100 is fine.
			char oRow[nCols];

			//Simple boolean switch used for the while loop.
			bool doneReadingFile = false;

			//While not done continue loop
			while(!doneReadingFile)
			{
				oRow[0]='\0';

				//Scan the first line to the oRow
				fscanf(fp, "%s", oRow);

				//If the row is not null
				if(strlen(oRow)!=0)
				{
					//Then we will increment howManyLinesInFile
					//And also set maximumWidth to howManyLinesInFile.
					howManyLinesInFile++;
					maximumWidth = nCols;
				}
				else
				{
					//If row is = 0, done = true, close fp
					doneReadingFile = true;
					fclose(fp);
				}
			}

		}
		else //If we cannot open the file.
		{
			puts("Cannot find that file,");
			done = true;
		}
		if(!done)
		{
			//A, B, C are the arrays used being declared here.
			char A[nRows][nCols];
			char B[nRows][nCols];
			char C[nRows][nCols];

			//Pointers to those arrays at the starting indices.
			char* old_p=&A[0][0];
			char* new_p=&B[0][0];
			char* other_p=&C[0][0];

			//Loop through the array by row and col and initialize the indices.
			for(int row = 0; row< nRows; row++)
			{
				for(int col = 0; col<nCols; col++)
				{
					//Initialize the pointers to the three arrays.
					//Doesn't matter with what, just getting them ready.
					A[row][col] = '-';
				    B[row][col] = '-';
					C[row][col] = '-';
				}
			}
			//Usuaslly have to be careful with file input, but since we read it before we can expect to read again.
			FILE* fp = fopen(filename, "r");

			//Read the actual file into the array at the ptr, old_p.
			readFileIntoArray(nRows, nCols, howManyLinesInFile,  maximumWidth, old_p, fp);

			//This will call the function generate and set the return value to the variable howManyGens.
			int howManyGens = generate(gens,  nRows,  nCols,  old_p, new_p, other_p, print, pause);

			printf("\nRan %d generations!\n", gens);
		}

	}//not done
	results = !done;
	return results;

}

/**
 * PlayOne carries out one generation. This is done based on the parameters provided.
 *
 * @param unsigned int nr, the number of rows in the petri dish
 * @param unsigned int nc, the number of columns in the petri dish
 * @param char* Old, the location of the upper left of starting petri dish
 * @param char* New, the location of the upper left of the ending petri dish
 * @return There is none, because results are in New array
 */
void PlayOne (unsigned int nr, unsigned int nc, char* Old, char* New)
{
	//Setting the values passed in to intergers to be used throughout the rest of the function.
	int nRows = nr;
	int nCols = nc;

	//This will loop through the array indices, and based on the rules set the fields.
	for(int row=0;row<nRows;row++)
	{
		for(int col=0; col<nCols; col++)
		{
			//There are three rules,
			// use occupied in old
			//use neighbors in old
			bool occupied = true;
			occupied = 	(getLetter(row,col,nCols, Old)=='x');

			//If there is an x in the spot then occupied is true.
			if(occupied
					&&((HowManyNeighbors(row, col, nRows, nCols, Old)<2)
							|| (HowManyNeighbors(row, col, nRows, nCols, Old)>3)))
			{//Death rule
				*(New + (row * nCols) + col)='o';
			}
			else if(occupied)
			{//Survival rule
				*(New + (row * nCols) + col)='x';
			}
			else if(HowManyNeighbors(row, col, nRows, nCols, Old)==3)
			{//Birth rule
				*(New + (row * nCols) + col)='x';

			}
			else
			{
				*(New + (row * nCols) + col)='o';
			}
		}
	}
}

/**
 * This function will print the usage of the program for command line running.
 */
void usage(void)
{
	puts("Usage: HW2 NR NC gens input [print] [pause]");
}
/*
 * This function will return the char at the given spot by pointer arithmitic.
 *
 * @param row The row of the index to get letter.
 * @param col The col of the index to get letter.
 * @param nCols The total number of columns in the generation.
 * @param *Old The pointer to the character to be returned after math.
 * @return The character that is in the specified index.
 */
char getLetter(int row, int col, int nCols, char* Old)
{
	return *(Old+ (row*nCols)+col);
}

/**
 * This function is used to calculate how many neighboors an index has.
 *
 * @param row The row of the index used to calculate neighboors around it.
 * @param col The col of the index used to calculate neighboors around it.
 * @param nRows The total rows.
 * @param nCols The total cols.
 * @param *Old The pointer to the index of which neighboors are to be calculated.
 */
int HowManyNeighbors(int row, int col, int nRows, int nCols, char* Old)
{
	//Need to initalize the variable to 0.
	int howManyN = 0;

	//We will search for neighbors clockwise from NorthWest
	if (row>0)
	{
		if(col>0)
		{
			if(getLetter(row-1, col-1,nCols, Old)=='x')//NW
			{
				howManyN++;
			}
		}
		if(getLetter(row-1, col,nCols, Old)=='x') //N
		{
			howManyN++;
		}
		if(col<(nCols-1))
		{
			if(getLetter(row-1, col+1,nCols, Old)=='x')//NE
			{
				howManyN++;
			}
		}
	}//can look north
	if(col>0)
	{
		if(getLetter(row, col-1,nCols, Old)=='x')//W
		{
			howManyN++;
		}
	}
	if(col<(nCols-1))
	{
		if(getLetter(row, col+1,nCols, Old)=='x')//E
		{
			howManyN++;
		}
	}
	if(row<nRows-1)
	{
		if(col>0)
		{
			if(getLetter(row+1, col-1,nCols, Old)=='x')//SW
			{
				howManyN++;
			}
		}
		if(getLetter(row+1, col,nCols, Old)=='x')//S
		{
			howManyN++;
		}
		if(col<(nCols-1))
		{
			if(getLetter(row+1, col+1,nCols, Old)=='x')//SE
			{
				howManyN++;
			}
		}
	}//can look south

	//Maybe not needed, but just in case
	if (howManyN > 8)
		perror("Cannot be more than 8.");

	return howManyN;
}

/**
 * This function is used to acually read the file into the array.
 *
 * @param nRows The integer used to store the number of rows.
 * @param nCols The integer used to store the number of cols.
 * @param howManyLinesInFile This is used to store the number of lines from the file.
 * @param maximumWidth This is used to set the maximum with (cols) of the space.
 * @param arp The pointer to the char where the beginning of the array is.
 * @param fp The pointer to the File handler to be used.
 */
void readFileIntoArray(int nRows, int nCols, int howManyLinesInFile, int maximumWidth, char* ar_p, FILE* fp)
{
	//This will iterate through the array, and fill it with o's to start.
	for(int row = 0; row< nRows; row++)
	{
		for(int col = 0; col<nCols; col++)
		{
			*(ar_p+(row*nCols)+col) = 'o';
		}
	}

	//This will then loop through the lines in file variable.
	for(int frow=0; frow< howManyLinesInFile; frow++)
	{
		//This is a character buffer for the data from the file.
		char fromFile[maximumWidth];

		//This fills the buffer with o's
		for(int i = 0; i<maximumWidth; i++)
		{
			fromFile[i]='o';
		}
		//Scan fp to fromFile
		fscanf(fp, "%s", fromFile);

		//This will loop through a
		for(int fcol=0; fcol<maximumWidth; fcol++)
		{
			for(int frow=0; frow<howManyLinesInFile; frow++)
			{
				//If what is stored at that spot in the buffer/array is an x
				//then we will use pointer arithmitic to set it to x in the array.
				if(fromFile[fcol]=='x')
				{
					int targetRow = frow+(nRows-howManyLinesInFile)/2;
					int targetCol = fcol+(nCols-maximumWidth)/2;
					*(ar_p+(targetRow*nCols)+targetCol) = 'x';
				}
			}
		}
	}
}

/**
 * This function is used to generate each iteration of the cells/board.
 *
 * @param gens The integer used to store the number of generations to run through.
 * @param nRows The integer used to store the total number of rows.
 * @param nCols The integer used to store the total number of cols.
 * @param *old_p The first pointer to the first array.
 * @param *new_p The second pointer to the second array.
 * @param *other_p THe third pointer to the third array.
 * @param print The character indicating whether or not the play through should be printed or not.
 * @param pause The character indicating whether or not the play though will pause after generations.
 * @return The integer representing the amount of generations it ran through.
 */
int generate(int gens,  int nRows,  int nCols,  char* old_p, char* new_p, char* other_p, char print, char pause)
{
	//The actual generations already ran through.
	int g = 0;

	//These are booleans switches that will help the control flow of the function.
	//If all organisms are dead then true.
	bool allOrganismsDead = false;

	//This means that the pattern was iterated twice. Helpful to know its not bugged.
	bool patternRepeated = false;

	//The main done boolean.
	bool done = false;

	//If first time, it will run through as true of course then switch.
	bool firstTime = true;
	bool lastTime = false;
	//This will loop through the generations and increment gensDone each time.
	for(int gensDone = 0; !done && (gensDone<gens); gensDone++)
	{
		if(!anyX(old_p, nRows, nCols))
		{
			allOrganismsDead = true;
			done = true;
			printf("All organisms are dead at Generation %d. :(\n", gensDone);
			printThis(nRows,nCols,old_p);
		}

		//Calls the play one function which will actually play the generation, subjecting it to the
		//rules of the Game of Life.
		PlayOne(nRows, nCols, old_p, new_p);

		//Increment g, after sucessful return from call
		g++;

		//If they aren't the same then we will check new_p and other_p.
		if(sameContent(old_p, new_p, nRows, nCols))
		{
			patternRepeated = true;
			done = true;
			puts("\nPattern repeated in one generations.");
			printThis(nRows,nCols,old_p);
		}

		if(firstTime)
		{
			printf("Generation 1:\n");
			printThis(nRows, nCols, old_p);
			allOrganismsDead = false;
			firstTime = false;
		}
		else
		{
			//If they aren't the same then we will check new_p and other_p.
			if(sameContent(old_p, other_p, nRows, nCols))
			{
				patternRepeated = true;
				puts("\nPattern repeated in two generations.");
				printThis(nRows,nCols,other_p);
				done = true;
			}
		}
		if(!done)
		{
			if(print=='y')
			{
				printf("Generation %d\n", g);
				printThis(nRows, nCols, new_p);
				printf("\n");
			}
			if(pause=='y')
			{
				puts("Paused waiting for input.");
				getc(stdin);//just waits for user input
			}
			char temp[nRows][nCols];

			char * tempptr = &temp[0][0];
			tempptr = old_p;
			//other_p = old_p;
			old_p = new_p;
			new_p = other_p;
			other_p = tempptr;
			//Musical chairs indeed, the other_p we don't care for,
			//It's like using a temporary variable to perform a swap.
		}

	}//end of generations
	//And return g because g is the actual count of the generations.
	return g;
}

/**
 * This function is used to check if there is an x in the array.
 *
 * @param *arr The pointer to the array to check.
 * @param nRows The total number of rows.
 * @param nCols The total number of cols.
 * @return True if there is an x, false otherwise.
 */
bool anyX(char* arr, int nRows, int nCols)
{
	//Start with the assumption there is no 'x' because was filled with o's.
	bool any = false;

	//Loop through the array indices.
	for(int row=0; !any && (row<nRows); row++)
	{
		for(int col=0; !any && (col< nCols); col++)
		{
			char letter = (char) getLetter(row,col,nCols, arr);
			if(letter == 'x')
			{
				//If there is an x then we switch boolean to true, and ret
				any = true;
			}
		}
	}
	return any;
}

/**
 * This function is used to check whether or not the two arrays pointed to by
 * the pointers have the same content.
 *
 * @param *one_p The pointer to the first array.
 * @param *another_p The pointer to the second array.
 * @param nRows The integer storing the total number of rows.
 * @param nCols The integer storing the total number of cols.
 * @return True if the arrays contain the same information and false otherwise.
 */
bool sameContent(char* one_p, char* another_p, int nRows, int nCols)
{
	//Assume they are not the same.
	bool same = true;

	for(int row=0; same && (row<nRows); row++)
	{
		for(int col=0; same && (col< nCols); col++)
		{
			//Check if they are the same
			if (*(one_p+ (row*nCols)+col) !=  *(another_p+ (row*nCols)+col)){
				same = false;
			}
		}
	}
	return same;
}

/**
 * This is a functon used to display the generation produced from each run of the Game
 * of Life.
 *
 * @param nRows The total number of rows in the array.
 * @param nCols The total number of cols in the array.
 * @param *old_p The pointer to the array to be printed.
 */
void printThis(int nRows, int nCols, char* old_p)
{
	for(int row=0;row<nRows;row++)
	{
		for(int col=0;col<nCols;col++)
		{
			 if ( *(old_p+ (row*nCols)+col) == 'x'){
				 printf("x");
			 }
			 else if (*(old_p+ (row*nCols)+col)  == 'o'){
				 printf("-");
			 }
		}
		printf("\n");
	}
}
