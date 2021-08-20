#ifndef BIBLIO_H
#define BIBLIO_H

#include <stdio.h>
#include "Constantes.h"

typedef struct data Data;
struct data {
    int movement;
    int gender;
    int index;
    double Vacc[NUMBER_OF_VACC_MAX];
};


void displayError(int error);

int creationOfDataSet(void);

void createHeader(FILE *pFi);

void lineProcessing(FILE *pFi, double sumAverages[NUMBER_OF_VACC_MAX], int nbValues[NUMBER_OF_VACC_MAX]);

void writeData(FILE *pFiModel, FILE *pFiWomen, double sumAveragesWomen[NUMBER_OF_VACC_MAX],
               int nbValuesWomen[NUMBER_OF_VACC_MAX], int movement, FILE *pFiMen,
               double sumAveragesMen[NUMBER_OF_VACC_MAX], int nbValuesMen[NUMBER_OF_VACC_MAX]);

void deleteHeader(FILE *pFi);

void creationOfHeader(FILE *pFi);

void fileNameObtention(char fileName[FILE_LENGTH], int fileNumber);

int retrieveGendersBysUsers(int genders[NUMBER_OF_USERS]);

int getMovement(char path[PATH_NAME_LENGTH]);

void writeDatas(FILE *pFi, Data data);

Data extractVacc(FILE *pPath, Data data);

int creationsOfModels(void);

#endif
