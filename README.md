# Programming Assignment # 2 — Game of Life# Abstract
```
Write a _C_ program that plays the _Game of Life_. Accept as arguments the size of the board, the initial
configuration, and the number of generations to play. Play that number of generations and display
the final configuration of the board.
```
## Outcomes

After successfully completing this assignment, you should be able to:

```
° Develop a C program that uses two-dimensional arrays
° Allocate memory for the arrays at run time
° Pass these arrays as arguments to functions
```
## Before Starting

Read Chapter 5 K&R pertaining to arrays and sections §§7.5–7.7 regarding file access. Pay particular
attention to §5.10 about command line access and §§5.7–5.9 about multi-dimensional arrays. Also
read the corresponding sections of Savitch, especially about the different ways of allocating two-
dimensional arrays.

## John Conway’s Game of Life

The Game of Life was invented by the mathematician John Conway and was originally described in
the April 1970 issue of _Scientific American_ (page 120). The Game of Life has since become an interest-
ing object of mathematical study and amusement, and it is the subject of many websites.

The game is played on a rectangular grid of cells, so that each cell has eight neighbors (adjacent
cells). Each cell is either occupied by an organism or not. A pattern of occupied and unoccupied
cells in the grid is called a _generation_. The rules for deriving a new generation from the previous gen-
eration are these:

1. _Death_. If an occupied cell has 0, 1, 4, 5, 6, 7, or 8 occupied neighbors, the organism dies (0 or 1
    of loneliness; 4 thru 8 of overcrowding).
_2. Survival._ If an occupied cell has two or three neighbors, the organism survives to the next genera-
    tion.
_3. Birth._ If an unoccupied cell has precisely three occupied neighbors, it becomes occupied by a
    new organism.

Examples can be found at [http://www.math.com/students/wonders/life/life.html.](http://www.math.com/students/wonders/life/life.html.)

Once started with an initial configuration of organisms (Generation 0), the game continues from one
generation to the next until one of three conditions is met for termination:

1. all organisms die, or

```
Project 2 ( 100 points)
Assigned: Tuesday, January 22 , 2019
Due: Monday, January 28, 2019 , 6:00 PM
```

2. the pattern of organisms repeats itself from a previous generation, or
3. a predefined number of generations is reached.

Note that for some patterns, a new generation is identical to the previous one — i.e., a steady state.
When this occurs, termination under condition #2 occurs. In some other common cases, a new
generation is identical to the second previous generation; that is, the board oscillates back and forth
between two configurations. In rare cases, a pattern repeats after an interval of more than two gen-
erations. In still other cases (some not so rare), a pattern replaces itself by a fixed offset in one or
both dimensions, thereby “flying” off the screen. In this assignment, you will be responsible for
terminating after a steady state is reached or an oscillation of two alternating patterns is reached.

In theory, the Game of Life is played on an infinite grid. In this assignment, your program will play
on a finite grid. The same rules apply, but squares beyond the edge of the grid are assumed to be
always unoccupied.

Note that, according to the rules, all changes for each generation are considered to take place simul-
taneously. Unfortunately, your program has to work through the board square-by-square. That is
why you always need to have at least two arrays: One holding the state of the board at the beginning
of the turn, and one which will be filled in with the state of the board at the end of the turn (which
will be the state at the beginning of the next turn). It turns out that you will also need a third array;
more about this later.

## Implementing your program

Your program must be called **HW2**. It needs to do several things:

- Read the arguments to the program from the command line.
- Read the initial configuration of the board from an **input** file.
- Allocate at least three arrays, each large enough to hold one generation of the game. Initialize the
    first generation with the initial configuration in the approximate center of the board.
- Play the game for as many generations as needed until one of the termination conditions above
    is met.
- Print out the final configuration, along with a message saying how many generations were played
    and under what condition the game terminated.

## Program Arguments and Input

The program should be invoked from the command line with the following arguments:

```
./HW2 NR NC gens inputfile [print] [pause]
```
where

- **NR** and **NC** are unsigned integers indicating the number of elements in the _y_ and _x_ directions of
    the grid, respectively. In other words, the number of rows and columns, respectively, in the grid
- **gens** is the number of generations to play. This value must be greater than zero. The program
    should halt after this number of generations. However, the program should halt prior to this
    number of generations if it determines that the game has reached a termination condition.
- **inputfile** is the name of a file containing a sequence of lines, each consisting of a sequence of
    **'x'** and **'o'** characters, indicating the occupied and unoccupied cells of the initial configuration.
    An **‘x’** indicates an occupied cell, an **‘o’** or a blank indicates an unoccupied cell. If a line is
    shorter than the width of the grid, cells to the right are considered unoccupied. If there are fewer


```
lines in the file than the height of the grid, cells below are considered unoccupied. Note: The
‘o’ characters are included to make it easier to see the patterns in the file. When you print the
grid, please only print blanks and ‘x’ characters.
```
- **print** is an optional argument with value of **'y'** or **'n'** indicating whether each generation (in-
    cluding generation 0) should be printed or displayed before proceeding to the next generation. If
    this item is missing, it defaults to **'n'.** Note: The user does not type the square brackets; they
    are used to denote that this argument is optional.
- **pause** is an optional argument with value of **'y'** or **'n'** indicating whether a keystroke is need-
    ed between generations. If this and/or the **print** item is missing, it defaults to **'n'**. It is not
    possible to specify a value for **pause** if you do not also specify a value for **print.**

After interpreting the program arguments, your program must open the **input** file, read its lines,
and initialize the configuration in the approximate center of your board in the _x-_ and _y-_ dimensions.
In other words, the pattern in the file starts in the upper-left corner of the grid; after you read it in,
determine the number of lines and the greatest width, and shift the pattern down and to the right as
needed to approximately center it.

_Example patterns_

Here is a simple pattern that happens to be a “still life” or steady state:

```
xx
xx
```
That is, the next generation starting from this pattern produces exactly the same pattern. Here is an-
other still life pattern:

```
oxo
xox
xox
oxo
```
The following pattern produces an oscillation between a vertical line of three occupied cells and a
horizontal line of three occupied cells

```
x
x
x
```
The following pattern is a well-studied one called the _R-Pentomino_.

```
oxx
xxo
oxo
```
It creates an interesting sequence of generations, including many sub-patterns that come, go, and/or
fly off the edge of the board, until it finally reaches a steady state after 1176 generations.

## Allocating your arrays

There are two ways in _C_ to create an array dynamically at run-time:

- Use the **malloc()** or **calloc()** functions to allocate memory from _The Heap_ and return a
    pointer to that memory. This is the most common practice in _C_. We will study it in class shortly.


- In **gcc** , newer versions of _C_ , and _C++,_ inside a function or compound statement, declare an
    array (allocated on _The Stack_ ) whose size is specified by an expression at run time. For example,
    the following is legal in **gcc** :
    **void function(unsigned int x, ...) {**
    **int A[x], B[x], C[x];**

```
/* use arrays A, B, and C */
...
} // Function
```
```
For a multi-dimensional array, any or all of the subscripts can be determined at run-time. The
rest of the subscripts would be compile-time constants.
```
```
Please note that where the memory is allocated from has important consequences. If it comes
from the heap, it stays allocated until either it is explicitly freed, or the program ends. If it is allo-
cated from the stack, it stays allocated only until the program exits from the block or function
where it was allocated. So, for example, you could allocate an array from the heap inside a func-
tion, and return it for use in another function. But if you allocate an array from the stack, you
can only use it inside that function, or inside functions called from that function (the same ap-
plies to blocks).
```
_Allocating multi-dimensional arrays at run-time_

§5.9 of Kernighan and Ritchie describe how the effect of a two-dimensional array can be achieved
by allocating an array of pointers, each pointer of which points to another array of **int**. Suppose
that you wish to allocate an array _B_ of **nr** rows of **nc** columns each, all from the heap. One way is
as follows:

```
int *B[ ];
unsigned int i, j, k;
```
```
B = malloc(nr * sizeof(int *)); // Allocate array of nr pointers
if (B) for (i = 0; i < nr; i++) {
B[i] = malloc(nc * sizeof (int)); // Allocate one row
if (!B[i]) exit(-1); /* error */
}
```
Then the array element of row **j** , column **k** , may be accessed as follows:

```
B[j][k] /* assuming that j < nr and k < nc */
```
You would pass it to a function like this:

**fun(nr, nc, B);**

And the function prototype would look like this:

**int fun(int nr, int nc, int* B[ ]);**

On the other hand, you can allocate from the stack like this:

**int B[nr][nc]; // Assume nr and nc already have values**

Then you could pass it to a function like this:


**fun(nr, nc, B);**

The function prototype would look like this:

**int fun(int nr, int nc, int B[ ][nc]);**

For this assignment, you must allocate the arrays from the stack.

_Sample code_

You will find starter code for this assignment on Canvas. The file **PrepHW2.zip** can be imported
into Eclipse as an existing project from an archive file; you must use this code as a starting point for
your own program. It demonstrates how to read the command-line arguments, how to read from
the input file, and how to create a two-dimensional array.

The file **Assignment2_testcases.zip** contains some sample input files. Unzip it into the
directory with your executable.

## Playing the Game

To play the game, it is suggested that you set up a function along the lines of the following to play
one generation:

```
void PlayOne (unsigned int nr, unsigned int nc, int Old[ ][nc],
int New[ ][nc]) {
/* loop through array New, setting each array element to
zero or one depending upon its neighbors in Old.*/
} // PlayOne
```
This can be called by the function **Life** using:

```
PlayOne(nr, nc, A, B);
```
The result is that **PlayOne** reads the contents of the first array (argument **A** ) and updates the sec-
ond array (argument **B** ). Subsequent generations might be played by

```
PlayOne(nr, nc, B, C);
PlayOne(nr, nc, C, A);
```
so that the generations cycle among three arrays. Note: this shows how the program would work,
conceptually. You should probably not code it exactly this way. Instead, always call PlayOne() using
the same variables as arguments, but each turn change which allocated array the variables point to.
For example, if you call the arguments p and q, at the start of the program you would set p = A, q =
B, spare = C. Then, at the beginning of the loop, you call PlayOne(nr, nc, p, q). At the end of the
loop, to get ready for the next turn, set temp = p, p = q, q = spare, spare = temp. Do you see a pat-
tern here? You need to decide (and document in a comment) what is true at each point in the loop;
that is the only practical way to keep it straight in your mind.

If the **pause** argument is set to **'y'** , the program should wait for the user to input something from
the keyboard between calls to **PlayOne()**. What the user inputs can be as short as the Enter key,
but be sure it is clear to the user what should be entered.

To test for termination conditions, you could adapt **PlayOne** to return values of zero or non-zero
to indicate whether anything has changed.

You will need to define and use several helper functions. For example:


- A function to compare two arrays, returning true if they are the same and false if they are
    different, for example. You would use this function to test for termination.
- A function which returns the number of neighbors a specified cell has.
- A function which returns whether a specified cell is occupied or not. Note that any cell off
    the edge of the board is considered unoccupied.

## Testing

Since we are using test-driven development, you need to test all the various functions, including the
helper functions. For example, test the function which tells if a cell is occupied by setting up a
known pattern, then looking at several cells, both within the grid and off the edges.

You should test your complete Game of Life with several initial conditions, including patterns that
you find on the web. When the graders test your program, they will use one or more standard input
files containing with typical patterns. The program arguments will match the input files.

## Deliverables

This project must be carried out on the course virtual machine. Your submission must include the
following:

```
° Two or more .c files and two or more .h files to implement your game.
° At least two test cases that demonstrate that your program works on a non-trivial pattern.
This goes in the same directory as the executable.
° A document called README.txt summarizing your program, how to run it, and detailing
any problems that you had. Also, if you borrowed all or part of the algorithm for this as-
signment, be sure to cite your sources and explain in detail how it works. You can put this in
the same directory as your source code.
```
Export your project and your test cases to an archive zip file named **PA 2 _** **_userName_** **.zip** , where
**_userName_** is replaced by your WPI username (i. e., login ID). Submit that zip file to _Canvas_.

This programming assignment is named **PA 2**_._ Programs submitted after the due date and time will
be tagged as late, and will be subject to the late homework policy.

## Grading

This assignment is worth one hundred ( 100 ) points. _Your program_ must _compile without errors in order to
receive_ any _credit._ It is suggested that before your submit your program, import your ZIP file and give
it a new project name, then compile and run it, just to be sure that it does not blow up and does not
contain surprising warnings.

## Additional Notes

Command line arguments in _C_ are explained in §5.10 of Kernighan and Ritchie_._ The function proto-
type of **main()** is

```
int main(int argc, char *argv[]);
```
The elements of the **argv** array are strings, which we have not yet studied in this course. The argu-
ment **argv[0]** contains the name of your program, **argv[1]** is the value **NR** , **argv[2]** is the
value **NC** , **argv[3]** is the value **gens** , and **argv[4]** is a string containing the name of the input


file. The numeric values can be extracted using the function **strtol()**. The file name can be used
directly in calls to **fopen()**. Sample usage is shown below:

```
#include <stdio.h>
#include <stdlib.h>
FILE *input; // The file holding the initial pattern
int nr; // Number of rows in the grid
int nc; // Number of columns in the grid
int gens; // Maximum number of generations to generate
if (argc < 5)
/* report error in command line */
char* endptr; // Address of invalid character, used by strtol()
nr = strtol(argv[1], &endptr, 10);
nc = strtol(argv[2], &endptr, 10);
gens = strtol(argv[3], &endptr, 10);
input = fopen(argv[4], "r");
if (!input)
/* report unable to open file */
/* continue with print and pause arguments */
```
Don’t forget that you need to look at argc to determine if either or both of the optional arguments
appear on the command line. Your program needs to handle the following cases:

- Too few arguments. This is an error, so print a message and exit the program.
- Just the required arguments. In that case, print and pause should take their default values.
- The print argument is specified but not pause.
- Both optional arguments are specified.
- Too many arguments. This is an error.

In Eclipse, you can specify command-line arguments when you create or modify a “Run configura-
tion”.

You can put the input file in the same directory as your source file.

We will cover how to read from a file in class.

Be sure to use Doxygen header comments on all the functions you write and on all functions you re-
use from the sample code. Here is a big tip: Decide what you want each function to do, then write
the header comment, then write the function. This forces you to decide what you want the function
to do, before you spend time writing it. If you are unsure, make your best guess – you can always
update the comments and code later. Be sure that you can run doxygen to generate the Web pages;
we will talk about this in class.


Don’t forget that you also need complete internal comments, including what each variable is used
for, ending conditions of loops, etc.

**Write and test your program step-by-step, always making sure you have a version which
compiles and runs, even if incomplete.** Consider writing the input and output functions first;
then you can use them while testing the other parts of the program.


