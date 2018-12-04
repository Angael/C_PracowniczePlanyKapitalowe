#ifndef DATATYPES_H
#define DATATYPES_H

typedef struct inputData {
   float tax;
   int   startWorkYear;
   int   endWorkYear;
   int   raiseIntervalDays;
   float raiseChance;
   int   startSalary;
   int   raiseAvgAmount;
   float miseryChance;
   float miseryIncomePercent;
} inputData;

#endif