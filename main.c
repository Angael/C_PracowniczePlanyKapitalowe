#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <menu.h>
//My files:
#include "myNcursesLib.h"
#include "fileOperations.h"
#include "dataTypes.h"

//Compile Command:
/*
gcc -Wall -o "main" "main.c" "myNcursesLib.c" "fileOperations.c" -lmenu -lncurses
	or
gcc -Wall -o "main" *.c -lmenu -lncurses && ./main
*/

#define FILE_LINE_SIZE 100
#define inputDataPropertyCount 9

//The only global variable, that saves a lot of:
// -problems due to no function overloading
// -writing pointers
// -
inputData inputData_values;


// typedef struct inputData {
//    float tax;
//    int   startWorkYear;
//    int   endWorkYear;
//    int   raiseIntervalDays;
//    float raiseChance;
//    int   startSalary;
//    int   raiseAvgAmount;
//    float miseryChance;
//    float miseryIncomePercent;
// } inputData;  

int main()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	//myFun();
	//todo remove
	char inputFileName[] = "myfile.txt";
	printw("Reading data from input file: %s\n", inputFileName);
	readDataFromFile(inputFileName, &inputData_values);
	//printw("tax in inputVal is: %.2f\n", values.tax);

	
	//todo
	//simulate();

	ncurses_startMyMenu();
	
	refresh();
	getch();
	endwin();
	
	return 0;
}




int mainBackup(void) {
 
    WINDOW * mainwin, * childwin;
    int      ch;
 
 
    /*  Set the dimensions and initial
	position for our child window   */
 
    int      width = 23, height = 7;
    int      rows  = 25, cols   = 80;
    int      x = (cols - width)  / 2;
    int      y = (rows - height) / 2;
 
 
    /*  Initialize ncurses  */
 
    if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
    }
 
 
    /*  Switch of echoing and enable keypad (for arrow keys)  */
 
    noecho();
    keypad(mainwin, TRUE);
 
 
    /*  Make our child window, and add
	a border and some text to it.   */
 
    childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 4, "Move the window");
    mvwaddstr(childwin, 2, 2, "with the arrow keys");
    mvwaddstr(childwin, 3, 6, "or HOME/END");
    mvwaddstr(childwin, 5, 3, "Press 'q' to quit");
 
    refresh();
 
 
    /*  Loop until user hits 'q' to quit  */
 
    while ( (ch = getch()) != 'q' ) {
 
	switch ( ch ) {
 
	case KEY_UP:
	    if ( y > 0 )
		--y;
	    break;
 
	case KEY_DOWN:
	    if ( y < (rows - height) )
		++y;
	    break;
 
	case KEY_LEFT:
	    if ( x > 0 )
		--x;
	    break;
 
	case KEY_RIGHT:
	    if ( x < (cols - width) )
		++x;
	    break;
 
	case KEY_HOME:
	    x = 0;
	    y = 0;
	    break;
 
	case KEY_END:
	    x = (cols - width);
	    y = (rows - height);
	    break;
 
	}
 
	mvwin(childwin, y, x);
	wrefresh(childwin);
    }
 
 
    /*  Clean up after ourselves  */
 
    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();
 
    return EXIT_SUCCESS;
}
void myFun(){
	int row,col;	
	char mesg[] = "Just a string";
	getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
									/* print the message at the center of the screen */
	mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again");
}