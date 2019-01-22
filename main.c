//! @file
//! @brief Main file, starting point of the program

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
//My files:
#include "myNcursesLib.h"
#include "fileOperations.h"
#include "dataTypes.h"

//Compile Command:
/* TODO: update github to use power function
gcc -Wall -o "main" "main.c" "myNcursesLib.c" "fileOperations.c" -lmenu -lncurses -lm
	or
gcc -Wall -o "main" *.c -lmenu -lncurses -lm && ./main
*/

//The only global variable, that saves a lot of:
// -problems due to no function overloading
// -unnecessary passing of pointers to functions
// Additionally I made this name complex enough that there should 
// never be naming conflicts
inputData inputData_values; /*!< The global variable that keeps values read from inputData.txt file.<br>
It's often used by other functions in different .c scripts*/

/** \file main.c
 * Starting point for the program.
 * It initializes Ncurses library, disables text cursor, calls \ref readDataFromFile function and finally starts my menu loop with \ref ncurses_startMyMenu
 */

int main()
{
	// Set up Ncures
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	// Start my function
	char inputFileName[] = "inputData.txt";
	printw("Reading data from input file: %s\n", inputFileName);
	readDataFromFile(inputFileName, &inputData_values);
	ncurses_startMyMenu();
	// End program
	refresh();
	//getch();
	endwin();
	return 0;
}