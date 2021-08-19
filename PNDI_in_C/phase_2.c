#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"
#include "tool.c"

void createHeader(FILE *pFi);

void initTab(int tab[NUMBER_OF_VACC_MAX]);

void lineProcessing(FILE *pFi, sumAverages[NUMBER_OF_VACC_MAX], nbValues[NUMBER_OF_VACC_MAX]);

void writeData(FILE *pFiModel, FILE *pFiWomen, int sumAveragesWomen[NUMBER_OF_VACC_MAX],
               int nbValuesWomen[NUMBER_OF_VACC_MAX], int movement, FILE *pFiMen,
               int sumAveragesMen[NUMBER_OF_VACC_MAX], int nbValuesMen[NUMBER_OF_VACC_MAX]);

int creationsOfModels(void) {
    // Structures
    double sumAveragesMen[NUMBER_OF_VACC_MAX];
    double sumAveragesWomen[NUMBER_OF_VACC_MAX];
    double nbValuesMen[NUMBER_OF_VACC_MAX];
    double nbValuesWomen[NUMBER_OF_VACC_MAX];

    FILE *pTrainSetFile = NULL;
    fopen_s(&pTrainSetFile, TRAIN_SET_FILE, "r");
    if (pTrainSetFile != NULL) {

        FILE *pModelFile = NULL;
        fopen_s(&pModelFile, MODEL_FILE, "w");
        if (pModelFile != NULL) {

            FILE *pMenModelFile = NULL;
            fopen_s(&pMenModelFile, MEN_MODEL_FILE, "w");
            if (pMenModelFile != NULL) {

                FILE *pWomenModelFile = NULL;
                fopen_s(&pWomenModelFile, WOMEN_MODEL_FILE, "w");
                if (pWomenModelFile != NULL) {

                    int currentMovement;
                    Data data;

                    createHeader(pWomenModelFile);
                    createHeader(pMenModelFile);
                    createHeader(pModelFile);

                    deleteHeader(pTrainSetFile);

                    fscanf_s(pTrainSetFile, "%d, %d, %d", &data.movement, &data.gender, &data.index);
                    while (!feof(pTrainSetFile)) {
                        currentMovement = data.movement;

                        initTab(sumAveragesMen);
                        initTab(sumAveragesWomen);
                        initTab(nbValuesMen);
                        initTab(nbValuesWomen);

                        while (!feof(pTrainSetFile) && currentMovement == movement) {
                            if (data.gender == FEMME) {
                                lineProcessing(pTrainSetFile, sumAveragesWomen, nbValuesWomen);
                            } else if (data.gender == HOMME) {
                                lineProcessing(pTrainSetFile, sumAveragesMen, nbValuesMen);
                            }

                            fscanf_s(pTrainSetFile, "%d, %d, %d", &data.movement, &data.gender, &data.index);
                            currentMovement = data.movement;
                        }

                        writeData(pModelFile, pWomenModelFile, sumAveragesWomen, nbValuesWomen, movement, pMenModelFile,
                                  sumAveragesMen, nbValuesMen);
                    }

                    fclose(pWomenModelFile);
                } else {
                    return FILE_OPEN;
                }

                fclose(pMenModelFile);
            } else {
                return FILE_OPEN;
            }

            fclose(pModelFile);
        } else {
            return FILE_OPEN;
        }

        fclose(pTrainSetFile);
    } else {
        return FILE_OPEN;
    }
}

void createHeader(FILE *pFi) {
    fprintf_s(pFi, "%s", "Mouvement");

    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++) {
        fprintf_s(pFi, ",%s", "Var");
    }
    fprintf_s(pFi, "\n");
}


void initTab(int tab[NUMBER_OF_VACC_MAX]) {
    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++)
        tab[i] = 0;
}

void lineProcessing(FILE *pFi, sumAverages[NUMBER_OF_VACC_MAX], nbValues[NUMBER_OF_VACC_MAX]) {
    double value;
    int iVacc;
    for (iVacc = 0; iVacc < NUMBER_OF_VACC_MAX; iVacc++) {
        fscanf_s(pFi, ",%lf", &value);
        sumAverages[iVacc] += value;
        nbValues[iVacc]++;
    }

    if (iVacc < NUMBER_OF_VACC_MAX) {
        sumAverages[iVacc] = '\0';
        nbValues[iVacc] = '\0';
    }
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

    for (int iVacc = 0;
         iVacc < NUMBER_OF_VACC_MAX
         && sumAveragesWomen[iVacc] != '\0'
         && sumAveragesMen[iVacc] != '\0'; iVacc++) {
        finalAverageWomen = sumAveragesWomen[iVacc] / nbValuesWomen[iVacc];
        fprintf_s(pFiWomen, ",%f", finalAverageWomen);

        finalAverageMen = sumAveragesMen[iVacc] / nbValuesMen[iVacc];
        fprintf_s(pFiMen, ",%f", finalAverageMen);

        totalAverage = (finalAverageWomen + finalAverageMen) / 2;
        fprintf_s(pFiMen, ",%f", totalAverage);
    }

    initTab(sumAveragesWomen);
    initTab(nbValuesWomen);
    initTab(sumAveragesMen);
    initTab(nbValuesMen);
}