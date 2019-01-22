#ifndef MAIN_H
#define MAIN_H

#include "dataTypes.h"
inputData inputData_values; /*!< The global variable that keeps values read from inputData.txt file */

/*! \mainpage Documentation Main Page
 *
 * \section intro Introduction
 *
 * This is a program for calculating  various statistics
 * of PPK program.
 * It simulates how long you will save, and how much.
 * Then it calculates the whole return value, including
 * variables like the amount of money in PPK,
 *  inflation, number of installments.<br>
 * 
 * Project is hosted on GitHub under link:<br>
 * \link https://github.com/Angael/C_PracowniczePlanyKapitalowe 
 * <br>
 * On GitHub you can find up to date instructions on how to compile and 
 * run this project.
 * 
 * \section b Controlling application
 * Use Up/Down arrow keys and Enter.
 *
 * \section c Inputting data
 *  \ref inputDataPage 
 * 
 */
/*! \page inputDataPage Input Data file
  \tableofcontents
  \section name Name of the file
  File with inuput data needs to be placed in the same directory as main.c .<br>
  It's name is always "inputData.txt"<br>
    This program loads inputData.txt automatically with it's start.



  \subsection howto How to place data in it
  Every line in this file describes one variable.<br>
  Variables are written on the beggining of a line and end with # sign.<br>
  Everything after # sign is a comment and doesn't affect the variable.<br>
  Because of how the program works, it's lines must not be too long, and that
  means the comment can't be infinitely long as C expects only so much data to be read
  in one line.
  \subsection subsection2 Example contents of inputData.txt
    1500# Miesieczny koszt utrzymania [int]<br>
    20#   Poczatek pracy [int rok zycia]<br>
    60#   Emerytura w [int rok zycia]<br>
    2000# Startowa Pensja brutto [int zl]<br>
    4.5#  Miesieczna szansa na podwyzke [float 0-100]<br>
    200#  Srednia Wysokosc podwyzki [float]<br>
    2.0#  Opcjonalny procent odkladany na PPK przez Pracownika [float 0-2]<br>
    2.5#  Opcjonalny procent odkladany na PPK przez Pracodawce [float 0-2.5]<br>
    120#  W ilu ratach ma byc wyplacane PKK [int 120-480]<br>
    2#    Roczny Wskaznik Inflacji w Procentach [float]
*/

/*! 
  Main Function starts Ncurses library functions
  and calls my own libraries, which then loop till 
  the program stops.
*/
void main();
void ncurses_Option_showLoadedData();

#endif