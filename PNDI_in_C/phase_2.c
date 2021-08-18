#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"

// Constantes
#define TRAIN_SET "trainSet.csv"
#define FI_MODEL "fiModel.csv"
#define FI_MODEL_MEN "fiModelMen.csv"
#define FI_MODEL_WOMEN "fiModelWomen.csv"
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

    FILE *pFiTrainSet = NULL;
    FILE *pFiModel = NULL;
    FILE *pFiMen = NULL;
    FILE *pFiWomen = NULL;

    fopen_s(&pFiTrainSet, TRAIN_SET, "r");
    fopen_s(&pFiModel, FI_MODEL, "w");
    fopen_s(&pFiMen, FI_MODEL_MEN, "w");
    fopen_s(&pFiWomen, FI_MODEL_WOMEN, "w");


    if ((pFiTrainSet != NULL) && (pFiModel != NULL) && (pFiMen != NULL) && (pFiWomen != NULL)) {
        char title[TITLE_LENGTH];
        char line[LINE_LENGTH];
        int error;
        int iLine = 1;
        int currentMovement;
        // pFiTrainSet  = se positionner sur la Line n° 1 de "trainSet.csv"
        // title = Ligne n° iLine pFiTrainSet
        error = fgets(title, TITLE_LENGTH, pFiTrainSet);
        // sortir title
        // error = fscanf_s(pFiTrainSet, "%d", &mov.move);
        iLine = posLineTrainSet(pFiTrainSet, iLine, line);

        while (!feof(pFiTrainSet)) {
            movement = fscanf_s(pFiTrainSet, "%d", &mov.move);
            currentMovement = movement;

            initTab(sumAveragesMen);
            initTab(sumAveragesWomen);
            initTab(nbValuesMen);
            initTab(nbValuesWomen);

            while (!feof(pFiTrainSet) && currentMovement == movement) {
                genderCode = (int) getField(line, 2);
                posLineTrainSet(pFiTrainSet, iLine, line);
                movement = fscanf_s(pFiTrainSet, "%d", &mov.move);
                if (genderCode == FEMME) {
                    lineProcessing(line, sumAveragesWomen, nbValuesWomen);
                } else if (genderCode == HOMME) {
                    lineProcessing(line, sumAveragesMen, nbValuesMen);
                }
                posLineTrainSet(pFiTrainSet, iLine, line);
                movement = fscanf_s(pFiTrainSet, "%d", &mov.move);
                currentMovement = movement;
            }

            writeData(pFiModel, pFiWomen, sumAveragesWomen, nbValuesWomen, movement, pFiMen, sumAveragesMen,
                      nbValuesMen);

            fclose(pFiTrainSet);
            fclose(pFiModel);
            fclose(pFiMen);
            fclose(pFiWomen);
        }

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