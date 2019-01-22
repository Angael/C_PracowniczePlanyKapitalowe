//! @file
//! @brief Library of functions focused on file manipulation like reading and writing to them.

#include "fileOperations.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "dataTypes.h"

/*! \fn void addValToInputData(int i, char s[], inputData* pValues)
 *  \brief Converts string s to a float. Then saves this float to
 * a specified, by line number i, property
 * 
 *  \param i Line number of a line in inputData.txt. Int
 *  \param s[] Is a string containing number.
 *  \param[out] pValues is an inputData structure pointer. Data read from file
 * is saved in this parameter.
 * 
 *  \return void
 */
void addValToInputData(int i, char s[], inputData* pValues){
	float num;
	//printw("%f\n", atof(s));
	num = atof(s);
	switch(i){
		case 1:
			//printw("case 1: float == %f\n", val);
			(*pValues).monthlyCostOfLiving = num;
			break;
		case 2:
			(*pValues).startWorkYear = num;
			break;
		case 3:
			(*pValues).endWorkYear = num;
			break;
		case 4:
			(*pValues).startSalary = num;
			break;
		case 5:
			(*pValues).raiseChance = num;
			break;
		case 6:
			(*pValues).raiseAvgAmount = num;
			break;
		case 7:
			(*pValues).optionalPkkEmployee = num;
			break;
		case 8:
			(*pValues).optionalPkkEmployer = num;
			break;
		case 9:
			(*pValues).liczbaRatPKK = num;
			break;		
		case 10:
			(*pValues).wskaznikInflacji = num;
			break;
		default:
			break;
            //Compiler Warning here is wrong, this function exits and has purpose
			//printw("error, too many lines\n");
	}
}

/*! \fn void readDataFromFile(char fileName[], inputData* pValues)
 *  \brief Function that opens file with name fileName[] and reads
 * it's data, passing it to variable's pointer in the parameters pValues.
 * 	\see addValToInputData
 *  \param fileName[] is a string filename
 *  \param[out] pValues is an inputData structure pointer. Data read from file
 * is saved in this parameter.
 * 
 *  \return void
 */
void readDataFromFile(char fileName[], inputData* pValues){
	FILE * pFile;
	char s[FILE_LINE_SIZE];

	pFile = fopen (fileName , "r");
	// int i is the line number of data from file
	int i = 1;
	while(!feof(pFile))
	{
		fgets(s, sizeof(s), pFile);
		char *ptr;
		//find memory address of # and cut the string there
		ptr = strchr(s, '#');
		if (ptr != NULL) {
			*ptr = '\0';
		}
		//todo remove comment
		//pValues without &, because it's already a pointer idk
		addValToInputData(i, s, pValues);
		//printw("num: %d\n", num);
		i++;
	}
	fclose (pFile);
    printw("Reading file complete - file closed.\n");
}

/*! \fn void saveSimulationToFile(monthStats simulation[], int length)
 *  \brief Writes simulation[] array to "simulation.txt" file in a nice form.
 *  \param simulation[] is an array of calculated month stats.
 *  \param length Describes how many months are in paramter simulation[]. Int
 */
void saveSimulationToFile(monthStats simulation[], int length){
	FILE *f = fopen(SIMULATION_FILENAME, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	int month_of_year, year_number;
	for(int i = 0; i<length; i++){
		// Month in format 1-12
		// Remember months nr start from nr 1, so we have to change 0 into 12
		month_of_year = simulation[i].monthNumber % 12;
		if (month_of_year == 0) month_of_year = 12;
		// Year extracted from number of months
		year_number = (simulation[i].monthNumber - month_of_year ) / 12 ;

		    //Print all data saved in struct
		fprintf(f, "   --- Month %d, Year: %d ---\n" , month_of_year, year_number);
		//fprintf(f, "%-12dMonth number\n" , simulation[i].monthNumber);
		
		fprintf(f, "%-12.2fGross income this month\n" , simulation[i].monthSalaryGross);
		fprintf(f, "%-12.2fNet income if using PKK\n" , simulation[i].monthSalaryNet);
		fprintf(f, "%-12.2fNet income if not using PKK\n\n" , simulation[i].monthSalaryNetWithoutPKK);
		fprintf(f, "%-12.2fTotal earnings if using PKK\n" , simulation[i].allEarnings);
		fprintf(f, "%-12.2fTotal earnings if not using PKK \n\n" , simulation[i].allEarningsWithoutPKK);
		fprintf(f, "%-12.2fTotal (earnings - expenses) if using PKK\n" , simulation[i].allRealEarnings);
		fprintf(f, "%-12.2fTotal (earnings - expenses) is not using PKK \n\n" , simulation[i].allRealEarningsWithoutPKK);
		fprintf(f, "%-12.2fEmployer cost \n" , simulation[i].kosztPracodawcy);
		fprintf(f, "%-12.2fAccumulated PKK \n\n" , simulation[i].odlozonePkk);
    
	}


	fclose(f);
}