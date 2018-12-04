/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "myNcursesLib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <menu.h>

#include "main.h"
#include "dataTypes.h"

//TODO: 
//How to get that defined value from main, but without passing as param?
//I duplicated it for now, but it's not elegant
#define inputDataPropertyCount 9

//TODO: split into smaller parts
void ncurses_startMyMenu(){
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	//arguments as follow: height, width, starty, startx 
	#define NOFO 6 //Number of Options
	WINDOW *menuwin = newwin(NOFO+2, xMax-0, yMax-(NOFO+2), 0);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);
	//char choices[3][4] = {"walk", "jog", "run"};
	char menu_choicess[NOFO][30] = {
                        "Simulate savings",
                        "Open Month by Month view",
                        "Save Simulation to file ...",
                        "Show Loaded data",
                        "Reload input data",
                        "Exit"
                  };
	int menu_choices;
	int highlight = 0;

	while(true){
		for(int i = 0; i<NOFO; i++){
			if(i == highlight){
				wattron(menuwin, A_REVERSE);
			}
			mvwprintw(menuwin, i+1, 1, menu_choicess[i]);
			wattroff(menuwin, A_REVERSE);

		}
        //clicked button
		menu_choices = wgetch(menuwin);
		switch(menu_choices){
			case KEY_UP:
				highlight--;
				if(highlight == -1){
					highlight = NOFO - 1;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == NOFO){
					highlight = 0;
				}
				break;
            case 10: //ENTER
                clickedOptionInMainMenu(highlight);
            default:
                //get character number
                //mvwprintw(menuwin, 1, 20, "%d", menu_choices);
                break;
		}
	}
}

// TODO: Finish all options in the main menu
void clickedOptionInMainMenu(int i){
    switch(i){
        case 0:
            printw("Function to be completed...\n");
            refresh();
			break;
        case 1:
            printw("Function to be completed...\n");
            refresh();
			break;
		case 2:
            printw("Function to be completed...\n");
            refresh();
            break;
		case 3:
            ncurses_Option_showLoadedData();
			break;
		case 4:
            printw("Function to be completed...\n");
            refresh();
			break;
		case 5:
            endwin();
            exit(0);
			break;
    }
}

void ncurses_Option_showLoadedData(){
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	//arguments as follow: height, width, starty, startx 
	WINDOW *menuLoadedData = newwin(inputDataPropertyCount+2, xMax-2, 0, 1);
	box(menuLoadedData, 0, 0);
    
    //Print all data saved in struct
    mvwprintw(menuLoadedData, 1, 1, "Wysokosc Podatku: %0.2f %%" , inputData_values.tax);
    mvwprintw(menuLoadedData, 2, 1, "Poczatek pracy: %d rok zycia" , inputData_values.startWorkYear);
    mvwprintw(menuLoadedData, 3, 1, "Emerytura w : %d rok zycia" , inputData_values.endWorkYear);
    mvwprintw(menuLoadedData, 4, 1, "Premie co: %d dni" , inputData_values.raiseIntervalDays);
    mvwprintw(menuLoadedData, 5, 1, "Szansa na premie: %.2f %%" , inputData_values.raiseChance);
    mvwprintw(menuLoadedData, 6, 1, "Startowa Pensja: %.2f zl" , inputData_values.startSalary);
    mvwprintw(menuLoadedData, 7, 1, "Srednia Wysokosc Premii: %.2f zl" , inputData_values.raiseAvgAmount);
    mvwprintw(menuLoadedData, 8, 1, "Szansa na nieszczescie przez rok: %.2f %%" , inputData_values.miseryChance);
    mvwprintw(menuLoadedData, 9, 1, "Procent Zarobkow w nieszczesciu: %.2f zl" , inputData_values.miseryIncomePercent);
    
    wattron(menuLoadedData, A_REVERSE);
    mvwprintw(menuLoadedData, 10, xMax/2, "Exit");
    wattroff(menuLoadedData, A_REVERSE);

    refresh();
	wrefresh(menuLoadedData);

    while(wgetch(menuLoadedData) != 10){}
    //when enter is pressed clear memory after that window
    delwin(menuLoadedData);
    clear();
    ncurses_startMyMenu();
    // 23# Wysokosc Podatku [float 0-100]
    // 19# Poczatek pracy [rok zycia]
    // 63# Emerytura w [rok zycia]
    // 30# Premie co [dni]
    // 100# Szansa na premie [float 0-100]
    // 2500# Startowa Pensja [zl]
    // 100# Srednia Wysokosc Premii [int]
    // 5# Szansa na nieszczescie przez rok [float 0-100]
    // 50# Procent Zarobkow w nieszczesciu [float 0-100]
    

}