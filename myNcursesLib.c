//! @file
//! @brief Library of functions focused on creating and managing Ncurses menus.

#include "myNcursesLib.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>

#include "main.h"
#include "dataTypes.h"

/*! \fn void ncurses_startMyMenu()
 *  \brief Starts loop where you press down or up keyboard buttons to highlight
 * menu option and press enter to select it.
 * \see clickedOptionInMainMenu
 *  \return void
 */
void ncurses_startMyMenu(){
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	//arguments as follow: height, width, starty, startx 
	WINDOW *menuwin = newwin(NOMenuOptions+2, xMax-0, yMax-(NOMenuOptions+2), 0);

	wrefresh(menuwin);

	keypad(menuwin, true);
	char menu_choicess[NOMenuOptions][50] = {
                        "Simulate savings and save to 'simulation.txt'",
                        "Show Loaded data",
                        "Reload input data",
                        "Exit"
                  };
	int menu_choices; // Here we store Value that we pressed
	int highlight = 0; // Which element to highlight at any given time

    //infinite loop for our menu and highlighting options 
	while(true){
        box(menuwin, 0, 0);
	    wrefresh(menuwin);
		for(int i = 0; i<NOMenuOptions; i++){
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
					highlight = NOMenuOptions - 1;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == NOMenuOptions){
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
        wrefresh(menuwin);
	}
}

/*! \fn void clickedOptionInMainMenu(int i)
 *  \brief Starts loop where you press down or up keyboard buttons to highlight
 * menu option and press enter to select it.<br>
 * This method calls other important methods in this program, see "See also:"
 * \see simulate To simulate and in process create simulation.txt
 * \see ncurses_Option_showLoadedData To show what data has been loaded from "inputData.txt"
 * \see readDataFromFile To reload data from "inputData.txt"
 *  \param i is the highlighted option index.
 *  \return void
 */
void clickedOptionInMainMenu(int i){
    int monthsCount = (inputData_values.endWorkYear - inputData_values.startWorkYear)*12;
    switch(i){
        case 0:
            simulate(monthsCount);
            //printw("Simulation Complete\n");
            refresh();
			break;
		case 1:
            ncurses_Option_showLoadedData();
			break;
		case 2:
            //printw("Reading data from input file: %s\n", "inputData.txt");
            readDataFromFile("inputData.txt", &inputData_values);
            refresh();
			break;
		case 3:
            endwin();
            exit(0);
			break;
    }
}

/*! \fn void ncurses_Option_showLoadedData()
 *  \brief Shows a box with all data loaded from "inputData.txt".<br>
 * The box requires clicking enter to hide it.
 */
void ncurses_Option_showLoadedData(){
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	//arguments as follow: height, width, starty, startx 
	WINDOW *menuSimulationResults = newwin(inputDataPropertyCount+2, xMax, 0, 0);
	box(menuSimulationResults, 0, 0);
    
    //Print all data saved in struct
    mvwprintw(menuSimulationResults, 1, 1, "Koszt utrzymania (Miesieczny): %d zl" , inputData_values.monthlyCostOfLiving);
    mvwprintw(menuSimulationResults, 2, 1, "Poczatek pracy: %d rok zycia" , inputData_values.startWorkYear);
    mvwprintw(menuSimulationResults, 3, 1, "Emerytura w : %d rok zycia" , inputData_values.endWorkYear);
    mvwprintw(menuSimulationResults, 4, 1, "Startowa Pensja: %.2f zl" , inputData_values.startSalary);
    mvwprintw(menuSimulationResults, 5, 1, "Szansa na premie: %.2f %% kazdego miesiaca" , inputData_values.raiseChance);
    mvwprintw(menuSimulationResults, 6, 1, "Srednia Wysokosc Premii: %.2f zl" , inputData_values.raiseAvgAmount);
    mvwprintw(menuSimulationResults, 7, 1, "Procent na PKK od Pracownika: %.2f %%" , inputData_values.optionalPkkEmployee);
    mvwprintw(menuSimulationResults, 8, 1, "Procent na PPK od Pracodawcy: %.2f %%" , inputData_values.optionalPkkEmployer);
    mvwprintw(menuSimulationResults, 9, 1, "Ile rat PKK: %d" , inputData_values.liczbaRatPKK);
    mvwprintw(menuSimulationResults, 10, 1, "Roczny Wskaznik Inflacji: %.2f %%" , inputData_values.wskaznikInflacji);
    
    wattron(menuSimulationResults, A_REVERSE);
    mvwprintw(menuSimulationResults, 11, xMax/2, "Exit");
    wattroff(menuSimulationResults, A_REVERSE);

    //refresh();
	wrefresh(menuSimulationResults);

    while(wgetch(menuSimulationResults) != 10){}
    //when enter is pressed clear memory after that window
    wclear(menuSimulationResults);
    wrefresh(menuSimulationResults);
    delwin(menuSimulationResults);
}

/*! \fn void ncurses_showSimulationResult(float _pkk)
 *  \brief Shows a box with a summary of the simulation.<br>
 * The box requires clicking enter to hide it.
 *  \param _pkk is how much money is collected in your PPK account in the end
 */
void ncurses_showSimulationResult(float _pkk){
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	//arguments as follow: height, width, starty, startx 
	WINDOW *menuSimulationResults = newwin(5+2, xMax, 0, 0);
	box(menuSimulationResults, 0, 0);
    

    int koniecEmerytury = inputData_values.endWorkYear + (inputData_values.liczbaRatPKK/12);
    //Print all data that is result of simulation
    mvwprintw(menuSimulationResults, 1, 1, "Zgromadzone srodki w PKK: %.2f zl" , _pkk);
    mvwprintw(menuSimulationResults, 2, 1, "Comiesieczna swiadczenie z PKK: %.2f" , _pkk/inputData_values.liczbaRatPKK );
    mvwprintw(menuSimulationResults, 3, 1, "Ilosc rat z PKK: %d" , inputData_values.liczbaRatPKK);
    mvwprintw(menuSimulationResults, 4, 1, "Emerytura skonczy sie w: %d rok zycia" , koniecEmerytury);
    mvwprintw(menuSimulationResults, 5, 1, "Szczegoly symulacji w 'simulation.txt' ..." );
    
    wattron(menuSimulationResults, A_REVERSE);
    mvwprintw(menuSimulationResults, 6, xMax/2, "Exit");
    wattroff(menuSimulationResults, A_REVERSE);

    //refresh();
	wrefresh(menuSimulationResults);

    while(wgetch(menuSimulationResults) != 10){}
    //when enter is pressed clear memory after that window
    wclear(menuSimulationResults);
    wrefresh(menuSimulationResults);
    delwin(menuSimulationResults);
}