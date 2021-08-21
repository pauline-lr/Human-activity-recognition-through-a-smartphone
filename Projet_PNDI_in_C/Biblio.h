#ifndef PROJET_PNDI_IN_C_BIBLIO_H
#define PROJET_PNDI_IN_C_BIBLIO_H

#include <stdio.h>
#include "Constants.h"



typedef struct data Data;
struct data {
    int movement;
    int gender;
    int index;
    double vAcc[NB_VACC + 1];
};

int creationOfDataSet(void);

void creationOfHeader(FILE *pFi);

Data extractData(char path_name[], int iFile, int index);

void writeData(Data data, FILE *pFichier);

int getMovement(char path[ACCESS_PATH_LENGTH]);

Data getGender(FILE *pFiDataSubjectsInfos, Data data, int iUser);

Data getVAcc(FILE *pFile, Data data);

int creationOfModels(void);

void createHeader(FILE *pFi);

void lineProcessing(FILE *pFi, double sumAverages[NB_VACC]);

void writeGender(FILE *pFi, int movement, double sumAveragesGender[NB_VACC], int nbGender);


#endif
