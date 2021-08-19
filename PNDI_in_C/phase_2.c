#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

// Constantes
#define LG_PATH  10

const char *getField(char *line, int num);
int posLineTrainSet(FILE *pFi, int iLine, char line[LINE_LENGTH]);
void initTab(int tab[NUMBER_OF_VACC_MAX]);
void lineProcessing(char line[LINE_LENGTH], sumAveragesWomen[NUMBER_OF_VACC_MAX], nbValuesWomen[NUMBER_OF_VACC_MAX]);
void writeData(FILE *pFiModel, FILE *pFiWomen, int sumAveragesWomen[NUMBER_OF_VACC_MAX],
               int nbValuesWomen[NUMBER_OF_VACC_MAX], int movement, FILE *pFiMen,
               int sumAveragesMen[NUMBER_OF_VACC_MAX], int nbValuesMen[NUMBER_OF_VACC_MAX]);

int creationsOfModels(void) {
    // Structures
    double sumAveragesMen[NUMBER_OF_VACC_MAX];
    double sumAveragesWomen[NUMBER_OF_VACC_MAX];
    double nbValuesMen[NUMBER_OF_VACC_MAX];
    double nbValuesWomen[NUMBER_OF_VACC_MAX];

    FILE *pTrainSetFile;
    fopen_s(&pTrainSetFile, TRAIN_SET_FILE, "r");
    if (pTrainSetFile != NULL) {

        FILE *pModelFile;
        fopen_s(&pModelFile, MODEL_FILE, "w");
        if (pModelFile != NULL) {

            FILE *pMenFile;
            fopen_s(&pMenFile, MODEL_MEN_FILE, "w");
            if (pMenFile != NULL) {

                FILE *pWomenFile;
                fopen_s(&pWomenFile, MODEL_WOMEN_FILE, "w");
                if (pWomenFile != NULL) {

                    char title[TITLE_LENGTH];
                    char line[LINE_LENGTH];
                    int error;
                    int iLine = 1;
                    int currentMovement;
                    // pTrainSetFile  = se positionner sur la Line n° 1 de "trainSet.csv"
                    // title = Ligne n° iLine pTrainSetFile
                    error = fgets(title, TITLE_LENGTH, pTrainSetFile);
                    // sortir title
                    // error = fscanf_s(pTrainSetFile, "%d", &mov.move);
                    iLine = posLineTrainSet(pTrainSetFile, iLine, line);

                    while (!feof(pTrainSetFile)) {
                        movement = fscanf_s(pTrainSetFile, "%d", &mov.move);
                        currentMovement = movement;

                        initTab(sumAveragesMen);
                        initTab(sumAveragesWomen);
                        initTab(nbValuesMen);
                        initTab(nbValuesWomen);

                        while (!feof(pTrainSetFile) && currentMovement == movement) {
                            genderCode = (int) getField(line, 2);
                            posLineTrainSet(pTrainSetFile, iLine, line);
                            movement = fscanf_s(pTrainSetFile, "%d", &mov.move);
                            if (genderCode == FEMME) {
                                lineProcessing(line, sumAveragesWomen, nbValuesWomen);
                            } else if (genderCode == HOMME) {
                                lineProcessing(line, sumAveragesMen, nbValuesMen);
                            }
                            posLineTrainSet(pTrainSetFile, iLine, line);
                            movement = fscanf_s(pTrainSetFile, "%d", &mov.move);
                            currentMovement = movement;
                        }

                        writeData(pModelFile, pWomenFile, sumAveragesWomen, nbValuesWomen, movement, pMenFile,
                                  sumAveragesMen, nbValuesMen);
                    }

                    fclose(pWomenFile);
                } else {
                    return FILE_OPEN;
                }

                fclose(pMenFile);
            } else {
                return FILE_OPEN;
            }

            fclose(pModelFile);
        } else {
            return FILE_OPEN;
        }

        fclose(pTrainSetFile);
        return NO_ERROR;
    } else {
        return FILE_OPEN;
    }
}

int posLineTrainSet(FILE *pFi, int iLine, char line[LINE_LENGTH]) {
    iLine++;
    fgets(line, LINE_LENGTH_VACC, pFi);
}


void initTab(int tab[NUMBER_OF_VACC_MAX]) {
    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++)
        tab[i] = 0;
}

void lineProcessing(char line[LINE_LENGTH], sumAverages[NUMBER_OF_VACC_MAX], nbValues[NUMBER_OF_VACC_MAX]) {
    double value;
    for (int iRow = 4; iRow < NUMBER_OF_VACC_MAX; iRow++) {
        value = (double) getField(line, iRow);
        sumAverages[iRow] += value;
        nbValues[iRow]++;
    }
}

const char *getField(char *line, int num) {
    const char *tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

void writeData(FILE *pFiModel, FILE *pFiWomen, int sumAveragesWomen[NUMBER_OF_VACC_MAX],
               int nbValuesWomen[NUMBER_OF_VACC_MAX], int movement, FILE *pFiMen,
               int sumAveragesMen[NUMBER_OF_VACC_MAX], int nbValuesMen[NUMBER_OF_VACC_MAX]) {
    double finalAverageWomen, finalAverageMen, totalAverage;

    fprintf_s(pFiModel, "\n");
    fprintf_s(pFiMen, "\n");
    fprintf_s(pFiWomen, "\n");
    fprintf_s(pFiModel, "%d", movement);
    fprintf_s(pFiMen, "%d", movement);
    fprintf_s(pFiWomen, "%d", movement);

    for (int iVacc = 0; iVacc < NUMBER_OF_VACC_MAX; iVacc++) {
        finalAverageWomen = sumAveragesWomen[iVacc] / nbValuesWomen[iVacc];
        fprintf_s(pFiWomen, ",%f", finalAverageWomen);

        finalAverageMen = sumAveragesMen[iVacc] / nbValuesMen[iVacc];
        fprintf_s(pFiMen, ",%f", finalAverageMen);

        totalAverage = (finalAverageWomen + finalAverageMen) / 2;
        fprintf_s(pFiMen, ",%f", finalAverageMen);
    }
}