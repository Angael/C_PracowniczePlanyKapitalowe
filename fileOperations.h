#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include "dataTypes.h"
/* Prototypes for the functions */
void addValToInputData(int i, char s[], inputData* pValues);

void readDataFromFile(char fileName[], inputData* pValues);

void saveSimulationToFile(monthStats simulation[], int length);

#endif