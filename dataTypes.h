#ifndef DATATYPES_H
#define DATATYPES_H

#define FILE_LINE_SIZE 100 //!< How long a line can be inside of the file
#define NOMenuOptions 4 //!< Number of Options in the Menu
#define inputDataPropertyCount 10 //!< How many lines are expected to be in "inputData.txt"
#define SIMULATION_FILENAME "simulation.txt" //!< how our output file is named

/**
 * Model for data from "inputData.txt"<br>
 * It's used globally, like a configuration file.
 */
typedef struct inputData {
   int   monthlyCostOfLiving; /*!< How much living costs per month. Used in
    simulation.txt to show how much money you are left with. 
   */
   int   startWorkYear;//!< at what age do you start working and collecting PPK
   int   endWorkYear;//!< at what age do you stop working and collecting PPK
   float startSalary;//!< Your starting monthly income at your company
   float raiseChance;//!< Chance to get a raise per month
   float raiseAvgAmount;//!< Amount of money added to income after raise
   float optionalPkkEmployee;//!< How much additionally employee gives to PPK
   float optionalPkkEmployer;//!< How much additionally employer gives to PPK
   int liczbaRatPKK;//!< In how many instalments do you want your PPK to be given to you
   float wskaznikInflacji;//!< Average yearly Inflation rate.
} inputData;

/**
 * Model for data of each month, that is stored in an array
 * for calculation.
 * Data from this models is then saved to "simulation.txt"
 */
typedef struct monthStats {
   int   monthNumber; //!< Month number, beginning with 1
   float monthSalaryGross; //!< Gross income this month
   float monthSalaryNet; //!< Net income this month
   float monthSalaryNetWithoutPKK; //!< Net income this month, if you didn't use PPK
   float allEarnings; //!< Total income from beggining of the job.
   float allEarningsWithoutPKK; //!< Total income from beggining of the job, if you didn't pay PPK
   float allRealEarnings; //!< Total income, but minus expenses
   float allRealEarningsWithoutPKK; //!< Total income if you didn't pay PPK, but minus expenses
   float kosztPracodawcy; //!< How much did Employer pay for your PPK this month
   float odlozonePkk; //!< Total PPK accumulated to this moment
} monthStats;

#endif