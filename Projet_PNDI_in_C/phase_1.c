#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Constants.h"
#include "Biblio.h"

const char movements[NB_MOVEMENTS][MOVEMENT_LENGTH] = {
        "dws", "ups", "jog", "sit", "std", "wlk"
};

const char paths[NB_PATH][PATH_LENGTH] = {
        "dws_1", "dws_2", "dws_11", "ups_3",
        "ups_4", "ups_12", "jog_9", "jog_16",
        "sit_5", "sit_13", "std_6", "std_14",
        "wlk_7", "wlk_8", "wlk_15"
};


int creationOfDataSet(void) {
    FILE *pFiTestSet = NULL;
    FILE *pFiTrainSet = NULL;

    fopen_s(&pFiTestSet, FI_TESTSET, "w");
    fopen_s(&pFiTrainSet, FI_TRAINSET, "w");

    if (pFiTrainSet == NULL) {
        printf("ERREUR : ouverture de trainSet.csv");
        return NO_OPEN_FILE;
    } else if (pFiTestSet == NULL) {
        printf("ERREUR : ouverture de testSet.csv");
        return NO_OPEN_FILE;
    } else {
        Data data;
        srand(time(NULL));

        creationOfHeader(pFiTrainSet);
        creationOfHeader(pFiTestSet);

        int index = 1;
        for (int iPath = 0; iPath < NB_PATH; iPath++) {

            for (int iFile = 1; iFile <= NB_FILE; iFile++) {

                data = extractData(paths[iPath], iFile, index);

                writeData(data, pFiTrainSet);

                if (rand() % 5 == 0) {
                    printf("Test : ");
                    writeData(data, pFiTestSet);
                }
                index++;
            }
        }
        fclose(pFiTrainSet);
        fclose(pFiTestSet);
    }
    return NO_ERROR;
}

void creationOfHeader(FILE *pFi) {
    fprintf_s(pFi, "%s,%s,%s", "Movement", "Gender", "Index");
    for (int i = 0; i < NB_VACC; i++)
        fprintf_s(pFi, ",%s", "Vacc");
    fprintf_s(pFi, "\n");
}

Data extractData(char pathName[], int iFile, int index) {
    FILE *pFile = NULL;
    FILE *pFiDataSubjectsInfos = NULL;
    Data data;
    char path[ACCESS_PATH_LENGTH];
    char currentPath[ACCESS_PATH_LENGTH];

    sprintf_s(currentPath, ACCESS_PATH_LENGTH, "%s/sub_%d.csv", pathName, iFile);
    sprintf_s(path, ACCESS_PATH_LENGTH, "%s/%s", PATH, currentPath);

    fopen_s(&pFile, path, "r");
    fopen_s(&pFiDataSubjectsInfos, FI_DATA_INFO, "r");

    if (pFiDataSubjectsInfos == NULL) {
        printf("ERREUR : ouverture de dataSubjectInfos.csv\n");
    } else if (pFile == NULL) {
        printf("ERREUR : ouverture de %s.csv\n", pathName);
    } else {
        data.movement = getMovement(pathName) + 1;

        data = getGender(pFiDataSubjectsInfos, data, iFile);

        data.index = index;

        data = getVAcc(pFile, data);

        fclose(pFile);
        printf("Index %d : Ajout du contenu de %s pour l'utilisateur numero %d\n", data.index, pathName, iFile);
        fclose(pFiDataSubjectsInfos);
    }
    return data;
}

int getMovement(char path[ACCESS_PATH_LENGTH]) {
    char movementName[MOVEMENT_LENGTH];
    strncpy_s(movementName, MOVEMENT_LENGTH, path,
              ABRV_MOVEMENT_LENGTH); // l'abréviation d'un movement est de 3 caractères
    int iMovement = 0;
    while (iMovement < NB_MOVEMENTS && strcmp(movementName, movements[iMovement]) != 0) {
        iMovement++;
    }
    return iMovement;
}

Data getGender(FILE *pFiDataSubjectsInfos, Data data, int iUser) {
    int code, uselessDataGender, gender;
    char headerDataSubjectsInfos[HEADER_DATA_LENGTH];
    fgets(headerDataSubjectsInfos, HEADER_DATA_LENGTH, pFiDataSubjectsInfos);
    int iGender = 0;
    while (!feof(pFiDataSubjectsInfos) && iGender < NB_FILE) {
        fscanf_s(pFiDataSubjectsInfos, "%d,%d,%d,%d,%d\n",
                 &code,
                 &uselessDataGender,
                 &uselessDataGender,
                 &uselessDataGender,
                 &gender);

        if (code == iUser)
            data.gender = gender;
        iGender++;
    }
    return data;
}

Data getVAcc(FILE *pFile, Data data) {
    int line;
    double uselessData;
    double accX, accY, accZ;

    int iVAcc;
    char header[HEADER_LENGTH_VACC];
    fgets(header, HEADER_LENGTH_VACC, pFile);
    for (iVAcc = 0; !feof(pFile) && iVAcc < NB_VACC; iVAcc++) {
        fscanf_s(pFile, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                 &line, &uselessData, &uselessData, &uselessData, &uselessData, &uselessData,
                 &uselessData, &uselessData, &uselessData, &uselessData, &accX, &accY, &accZ);
        data.vAcc[iVAcc] = sqrt(pow(accX, 2) + pow(accY, 2) + pow(accZ, 2));
    }

    if (iVAcc < NB_VACC)
        data.vAcc[iVAcc] = '\0';

    return data;
}


void writeData(Data data, FILE *pFichier) {
    fprintf_s(pFichier, "%d,%d,%d", data.movement, data.gender, data.index);

    for (int iVAcc = 0; isnan(data.vAcc[iVAcc]) != 1 && iVAcc < NB_VACC; iVAcc++) {
        fprintf_s(pFichier, ",%lf", data.vAcc[iVAcc]);
    }
    fprintf_s(pFichier, "\n");
}

