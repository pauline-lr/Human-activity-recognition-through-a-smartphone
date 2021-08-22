#include <stdio.h>
#include <math.h>

#include "Constants.h"
#include "Biblio.h"


int creationOfModels(void) {
    FILE* pFiTrainSet = NULL;
    FILE* pFiModel = NULL;
    FILE* pFiMen = NULL;
    FILE* pFiWomen = NULL;

    fopen_s(&pFiTrainSet, FI_TRAINSET, "r");
    fopen_s(&pFiModel, FI_MODEL, "w");
    fopen_s(&pFiMen, FI_MODEL_MEN, "w");
    fopen_s(&pFiWomen, FI_MODEL_WOMEN, "w");

    if (pFiTrainSet == NULL) {
        printf("ERREUR : ouverture de trainSet.csv");
        return NO_OPEN_FILE;
    }
    else if (pFiModel == NULL) {
        printf("ERREUR : ouverture de model.csv");
        return NO_OPEN_FILE;
    }
    else if (pFiMen == NULL) {
        printf("ERREUR : ouverture de menModel.csv");
        return NO_OPEN_FILE;
    }
    else if (pFiWomen == NULL) {
        printf("ERREUR : ouverture de womenModel.csv");
        return NO_OPEN_FILE;
    }
    else {
        createHeader(pFiWomen);
        createHeader(pFiMen);
        createHeader(pFiModel);

        char header[HEADER_LENGTH];
        int currentMovement;


        Data data;
        double sumAveragesMen[NB_VACC] = { 0 };
        double sumAveragesWomen[NB_VACC] = { 0 };

        int nbMen = 0;
        int nbWomen = 0;

        fgets(header, HEADER_LENGTH, pFiTrainSet);

        while (!feof(pFiTrainSet)) {
            fscanf_s(pFiTrainSet, "%d, %d, %d", &data.movement, &data.gender, &data.index);
            currentMovement = data.movement;

            while (!feof(pFiTrainSet) && data.movement == currentMovement) {
                if (data.gender == WOMEN) {
                    nbWomen++;
                    lineProcessing(pFiTrainSet, sumAveragesWomen);
                    printf("Index %d - Mouvement %d - ecriture d'une femme\n", data.index, data.movement);
                }
                else if (data.gender == MEN) {
                    nbMen++;
                    lineProcessing(pFiTrainSet, sumAveragesMen);
                    printf("Index %d - Mouvement %d - ecriture d'un homme\n", data.index, data.movement);
                }

                fscanf_s(pFiTrainSet, "/n");
                fscanf_s(pFiTrainSet, "%d, %d, %d", &data.movement, &data.gender, &data.index);
            } // fin bloc 2

            writeModel(pFiModel, currentMovement, sumAveragesMen, sumAveragesWomen, nbWomen, nbMen);
            writeGender(pFiWomen, currentMovement, sumAveragesWomen, nbWomen);
            writeGender(pFiMen, currentMovement, sumAveragesMen, nbMen);

            for (int iVAcc = 0; iVAcc < NB_VACC; iVAcc++) {
                sumAveragesWomen[iVAcc] = 0;
                sumAveragesMen[iVAcc] = 0;
            }

            nbMen = 0;
            nbWomen = 0;
        } // fin bloc 1

        fclose(pFiTrainSet);
        fclose(pFiWomen);
        fclose(pFiMen);
        fclose(pFiModel);
    }
    return NO_ERROR;
}

void createHeader(FILE* pFi) {
    fprintf_s(pFi, "%s", "Movement");

    for (int i = 0; i < NB_VACC; i++) {
        fprintf_s(pFi, ",%s", "Var");
    }
    fprintf_s(pFi, "\n");
}

void lineProcessing(FILE* pFi, double sumAverages[NB_VACC]) {
    double value;
    int iVacc;
    fscanf_s(pFi, ",%lf", &value);

    for (iVacc = 0; iVacc < NB_VACC; iVacc++) {
        sumAverages[iVacc] += value;
        fscanf_s(pFi, ",%lf", &value);
    }

    if (iVacc < NB_VACC) {
        sumAverages[iVacc] = '\0';
    }
}

void writeModel(FILE* pFiModel, int movement, double sumAveragesMen[NB_VACC], double sumAveragesWomen[NB_VACC], int nbWomen, int nbMen) {
    fprintf(pFiModel, "%d", movement);
    for (int iVacc = 0; iVacc < NB_VACC; iVacc++)
        fprintf(pFiModel, ",%lf", (sumAveragesMen[iVacc] + sumAveragesWomen[iVacc]) / (nbMen + nbWomen));
    fprintf(pFiModel, "\n");
}

void writeGender(FILE* pFi, int movement, double sumAveragesGender[NB_VACC], int nbGender) {
    fprintf(pFi, "%d", movement);
    for (int iGender = 0; iGender < NB_VACC && isnan(sumAveragesGender[iGender]) != 1; iGender++) {
        fprintf(pFi, ",%lf", sumAveragesGender[iGender] / nbGender);
    }
    fprintf(pFi, "\n");
}