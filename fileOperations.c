#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "dataTypes.h"

#define FILE_LINE_SIZE 100
#define inputDataPropertyCount 9



//Order of data in input file matters
void addValToInputData(int i, char s[], inputData* pValues){
	int num;
	num = atof(s);
	switch(i){
		case 1:
			//printw("case 1: float == %f\n", val);
			(*pValues).tax = num;
			break;
		case 2:
			(*pValues).startWorkYear = num;
			break;
		case 3:
			(*pValues).endWorkYear = num;
			break;
		case 4:
			(*pValues).raiseIntervalDays = num;
			break;
		case 5:
			(*pValues).raiseChance = num;
			break;
		case 6:
			(*pValues).startSalary = num;
			break;
		case 7:
			(*pValues).raiseAvgAmount = num;
			break;
		case 8:
			(*pValues).miseryChance = num;
			break;
		case 9:
			(*pValues).miseryIncomePercent = num;
			break;
		default:
            //Warning here is wrong, this function exits and has purpose
			printw("error, too many lines\n");
	}
}
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