#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"
#include "tool.c"

void createHeader(FILE* pFi);

void initTab(double tab[NUMBER_OF_VACC_MAX]);

void lineProcessing(FILE* pFi, double sumAverages[NUMBER_OF_VACC_MAX], int nbValues[NUMBER_OF_VACC_MAX]);

void writeData(FILE *pFiModel, FILE *pFiWomen, double sumAveragesWomen[NUMBER_OF_VACC_MAX],
               int nbValuesWomen[NUMBER_OF_VACC_MAX], int movement, FILE *pFiMen,
               double sumAveragesMen[NUMBER_OF_VACC_MAX], int nbValuesMen[NUMBER_OF_VACC_MAX]);

int creationsOfModels(void) {
    FILE *pFiTrainSet = NULL;
    FILE *pFiModel = NULL;
    FILE *pFiMen = NULL;
    FILE *pFiWomen = NULL;

    fopen_s(&pFiTrainSet, TRAIN_SET_FILE, "r");
    fopen_s(&pFiModel, MODEL_FILE, "w");
    fopen_s(&pFiMen, MEN_MODEL_FILE, "w");
    fopen_s(&pFiWomen, WOMEN_MODEL_FILE, "w");


    if ((pFiTrainSet != NULL) && (pFiModel != NULL) && (pFiMen != NULL) && (pFiWomen != NULL)) {
        int currentMovement;
        Data data;

        createHeader(pFiWomen);
        createHeader(pFiMen);
        createHeader(pFiModel);

        deleteHeader(pFiTrainSet);

        fscanf_s(pFiTrainSet, "%d, %d, %d", &data.movement, &data.gender, &data.index);
        while (!feof(pFiTrainSet)) {
            currentMovement = data.movement;
            int movement = currentMovement;

            double sumAveragesMen[NUMBER_OF_VACC_MAX] = {0};
            double sumAveragesWomen[NUMBER_OF_VACC_MAX] = {0};
            int nbValuesMen[NUMBER_OF_VACC_MAX] = {0};
            int nbValuesWomen[NUMBER_OF_VACC_MAX] = {0};


            while (!feof(pFiTrainSet) && currentMovement == movement) {
                if (data.gender == FEMME) {
                    lineProcessing(pFiTrainSet, sumAveragesWomen, nbValuesWomen);
                } else if (data.gender == HOMME) {
                    lineProcessing(pFiTrainSet, sumAveragesMen, nbValuesMen);
                }

                fscanf_s(pFiTrainSet, "%d, %d, %d", &data.movement, &data.gender, &data.index);
                currentMovement = data.movement;
            }
            writeData(pFiModel, pFiWomen, sumAveragesWomen, nbValuesWomen, data.movement, pFiMen, sumAveragesMen,nbValuesMen);
        }
        fclose(pFiTrainSet);
        fclose(pFiModel);
        fclose(pFiMen);
        fclose(pFiWomen);
    } else {
        return FILE_OPEN;
    }
}

void createHeader(FILE* pFi){
    fprintf_s(pFi, "%s", "Mouvement");

    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++) {
        fprintf_s(pFi, ",%s", "Var");
    }
    fprintf_s(pFi, "\n");
}


void initTab(double tab[NUMBER_OF_VACC_MAX]) {
    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++)
        tab[i] = 0;
}

void lineProcessing(FILE* pFi, double sumAverages[NUMBER_OF_VACC_MAX], int nbValues[NUMBER_OF_VACC_MAX]) {
    double value;
    int iVacc;
    for (iVacc = 0; iVacc < NUMBER_OF_VACC_MAX; iVacc++) {
        fscanf_s(pFi, ",%lf", &value);
        sumAverages[iVacc] += value;
        nbValues[iVacc]++;
    }

    if(iVacc < NUMBER_OF_VACC_MAX){
        sumAverages[iVacc] = '\0';
        nbValues[iVacc] = '\0';
    }
}

void writeData(FILE *pFiModel, FILE *pFiWomen, double sumAveragesWomen[NUMBER_OF_VACC_MAX],
               int nbValuesWomen[NUMBER_OF_VACC_MAX], int movement, FILE *pFiMen,
               double sumAveragesMen[NUMBER_OF_VACC_MAX], int nbValuesMen[NUMBER_OF_VACC_MAX]) {
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
}