//! @file
//! @brief Library of functions focused on simulating PKK returns, expenses. <br> Mainly math.


#include "simulate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curses.h>
#include <time.h>
#include <math.h>

#include "main.h"
#include "myNcursesLib.h"
#include "dataTypes.h"

#define placaMinimalna 2100
#define miesiecznaDoplataOdPanstwa 20
#define startowaDoplataOdPanstwa 250

/**
 * Obliczenia przeprowadzono analogicznie do strony:
 * http://e-prawapracownika.pl/3458/obliczyc-wynagrodzenie-netto-2018/
 * i
 * https://pracowniczeplanykapitalowe.org.pl/
 **/

/*! \fn void simulate(int monthsCount)
 *  \brief Simulates every month of giving money to PPK. <br>
 * This function exists to fill array of monthStats with data. <br>
 * This method calls other methods in this library, see "See also:"
 * \see getRaiseValue
 * \see getNetGain
 * \see getValueAfterInflation
 *  \param monthsCount is number of months to simulate. Int
 *  \return void
 */
void simulate(int monthsCount){
    time_t t;
    /* Random numbers for randomizing getting a Raise */
    srand((unsigned) time(&t));

    monthStats completeSimulationResult[monthsCount];
    float grossIncome = inputData_values.startSalary; // Monthly
    float allEarnings = 0; 
    float allEarningsWithoutPKK = 0;
    float allRealEarnings = 0;   //"Real" means we substract all costs of living
    float allRealEarningsWithoutPKK = 0;
    float odlozonePpk = 250; // Powitalna wartosc
    int i, year_number, month_of_year;
    
    for(i = 0; i<monthsCount; i++){
        float raiseValue = getRaiseValue(i+1);
        grossIncome += raiseValue;
        float netGain = getNetGain(grossIncome);

        float kosztPkkPracownika = grossIncome * (2+inputData_values.optionalPkkEmployee) * 0.01; // *0.01 bo to procenty a sa w wartosciach od 0 do 100
        allEarnings += netGain - kosztPkkPracownika;
        allEarningsWithoutPKK += netGain;

        allRealEarnings += netGain - kosztPkkPracownika - inputData_values.monthlyCostOfLiving;
        allRealEarningsWithoutPKK += netGain - inputData_values.monthlyCostOfLiving;

        float kosztPracodawcy = grossIncome * (1.5+inputData_values.optionalPkkEmployer) * 0.01;
       
        // Dodawanie do odlozonego Pkk
        if(i%12 == 0 && i != 0){
            odlozonePpk += 240; // Roczna doplata od panstwa
        }

    	month_of_year= (i+1) % 12;
		if (month_of_year == 0) month_of_year = 12;
    	// Year extracted from number of months
    	year_number = (i+1 - month_of_year ) / 12 ;
        
        odlozonePpk += kosztPracodawcy + kosztPkkPracownika;

        completeSimulationResult[i] = (monthStats){
            i+1, 
            grossIncome, 
            netGain - kosztPkkPracownika, 
            netGain, 
            allEarnings,
            allEarningsWithoutPKK, 
            allRealEarnings,
            allRealEarningsWithoutPKK, 
            //kosztPracodawcy,
            kosztPracodawcy,
            getValueAfterInflation(odlozonePpk, year_number)
        };
    }
    saveSimulationToFile(completeSimulationResult, monthsCount);
    ncurses_showSimulationResult(getValueAfterInflation(odlozonePpk, year_number));
}

// Mieszam angielski i polski by krotsze nazwy wychodzily
// , dalo sie to przeczytac i nie bylo dlugich linijek.
// Niestety nie dziala mi na tym linuksie polska klawiatura

/*! \fn getNetGain(float grossIncome)
 *  \brief This function returns net value of income this month.
 *  \param grossIncome is your gross income per month (Brutto). Float
 *  \return float Net gain/income this month.
 */
float getNetGain(float grossIncome){
    // W tej funkcji jest duzo niepotrzebnych zmiennych, ktore jednak ulatwiaja
    // pielegnacje i zrozumienie tego kodu
    float kosztUzyksPrzychodu = 120; // Usredniona wartosc
    float kwotaWolnaOdPodatku = 50;  //Usredniona wartosc na potrzeby tego projektu, bo nie o zarobki tu chodzi


    float skladki = grossIncome*(0.0976 + 0.015 + 0.0245);
    float podstSkladkiZdrow = grossIncome - skladki;
    float skladkaUbezpZdrow = podstSkladkiZdrow * 0.09;
    //Zaliczka na podatek dochodowy
    float a = 0.18 * (podstSkladkiZdrow - kosztUzyksPrzychodu);
    float zaliczkaPD_przed = a - kwotaWolnaOdPodatku;
    
    float b = podstSkladkiZdrow * 0.0775;
    float zaliczkaPD_doWplacenia = a - zaliczkaPD_przed - b;

    float Netto = grossIncome - skladki - skladkaUbezpZdrow - zaliczkaPD_doWplacenia;

    return Netto;
}

/*! \fn float getRaiseValue()
 *  \brief This function returns the size of the increase in income.<br>
 * It can return 0 or inputData_values.raiseAvgAmount depending on chance from "inputData.txt"
 *  \return float of the increase in income
 */
float getRaiseValue(){
    bool dajemyPodwyzke = (rand() % 100) < inputData_values.raiseChance;
    if(dajemyPodwyzke){
        return inputData_values.raiseAvgAmount;
    }
    return 0;
}

/*! \fn double getValueAfterInflation(float value, int year)
 *  \brief Returns the value adjusted for inflation after <year> of years.
 *  \param value is your gross income per month (Brutto). Float
 *  \param year is your gross income per month (Brutto). Float
 * \return the value adjusted for inflation after <year> of years. Double
 */
double getValueAfterInflation(float value, int year){
    return (pow(inputData_values.wskaznikInflacji / 100 + 1, year + 1) * value);
}
