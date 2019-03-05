/**
 * This is a header file for the production.c file. It contains all
 * the functions that are needed in the file. The functions have comments
 * explaining what they do in the actual .c files.
 *
 *  Created on: January 31, 2019
 *      Author: Tom Graham
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include <stdio.h>

bool production(int argc, char* argv[]);
void PlayOne (unsigned int nr, unsigned int nc, char* Old, char* New);
void usage(void);
char getLetter(int row, int col, int nCols, char* Old);
int HowManyNeighbors(int row, int col, int nRows, int nCols, char* Old);
void readFileIntoArray(int nRows, int nCols, int howManyLinesInFile, int maximumWidth, char* ar_p, FILE* fp);
int generate(int gens,  int nRows,  int nCols,  char* old_p, char* new_p, char* other_p, char print, char pause);
bool anyX(char* arr, int nRows, int nCols);
bool sameContent(char* one_p, char* another_p, int nRows, int nCols);
void printThis(int nRows, int nCols, char* old_p);

#endif /* PRODUCTION_H_ */
