#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "header.h"
#include "tool.c"


void creationOfHeader(FILE *pFi);
void fileNameObtention(char fileName[FILE_LENGTH], int fileNumber);
int retrieveGendersBysUsers(int genders[NUMBER_OF_USERS]);
int getMovement(char path[PATH_NAME_LENGTH]);
void deleteHeader(FILE *pFi) ;
void writeDatas(FILE *pFi, Data data);
Data extractVacc(FILE *pPath, Data data);

int creationOfDataSet(void) {
    /*je récupère d'abord tous les genres que je place dans un tableau
     * afin d'ouvrir le fichier "data_subjects_info.csv" une seule fois*/
    int gendersOfUsers[NUMBER_OF_USERS];
    retrieveGendersBysUsers(gendersOfUsers);


    FILE *pTrainSetFile = NULL;
    fopen_s(&pTrainSetFile, TRAIN_SET_FILE, "w+");
    if (pTrainSetFile != NULL) {

        FILE *pTestSetFile = NULL;
        fopen_s(&pTestSetFile, TEST_SET_FILE, "w+");
        if (pTestSetFile != NULL) {
            // créer les entête
            /*Pas dans le DA mais remarque de la prof à ce sujet*/
            creationOfHeader(pTrainSetFile);
            creationOfHeader(pTestSetFile);

            //Initialisation random
            srand(time(NULL));
            // intialisation structure enregistrements
            Data data;
            /*à mettre dans la 3ème colonne (cf. structure des fichier test et train
             * dans les consignes)
             * l'index va de 1 à 360 (360 pour NBPATH * NBFILES)*/
            data.index = 1;

            for (int iPath = 0; iPath < NUMBER_OF_PATHS; iPath++) {
                // intialisation du path en cours
                char fileName[PATH_LENGTH];
                char path[PATH_NAME_LENGTH];
                strcpy_s(path, PATH_NAME_LENGTH, paths[iPath]);

                // récupérer le mouvement
                data.movement = getMovement(path) + 1;

                for (int iFile = 0; iFile < NUMBER_OF_FILES; iFile++) {
                    //  récupérer le nom du fichier
                    fileNameObtention(fileName, iFile + 1);

                    // ouvrir le fichier avec son nom
                    FILE *pFile;
                    char accessPath[LENGTH_ACCESS_PATH] = "A_DeviceMotion_data/";
                    strcat_s(accessPath, LENGTH_ACCESS_PATH, path);
                    strcat_s(accessPath, LENGTH_ACCESS_PATH, "/");
                    strcat_s(accessPath, LENGTH_ACCESS_PATH, fileName);

                    fopen_s(&pFile, accessPath, "r");

                    if (pFile != NULL) {
                        data.gender = gendersOfUsers[iFile];

                        /*Dans les consignes on ne spécifie pas que le genre doit
                         * être écrit en toutes lettres, il est donc plus simple dans
                         * la manipulation des fichiers de garder un système de code
                         * (0 pour femme, 1 pour homme)
                         * donc plus de test sur le genre */

                        // récupération des Vacc
                        data = extractVacc(pFile, data);

                        // écrire le mouvement, genre et index dans train
                        writeDatas(pTrainSetFile, data);

                        // écrire un test random
                        if (rand() % 5 == 0)
                            writeDatas(pTestSetFile, data);

                    } else {
                        return FILE_OPEN;
                    }

                    data.index++;
                }
            }
            fclose(pTestSetFile);
        } else {
            return FILE_OPEN;
        }
        fclose(pTrainSetFile);
        return NO_ERROR;
    } else {
        return FILE_OPEN;
    }
}

void creationOfHeader(FILE *pFi) {
    fprintf_s(pFi, "%s,%s,%s", "Movement", "Gender", "Index");
    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++)
        fprintf_s(pFi, ",%s", "Vacc");
}

void fileNameObtention(char fileName[FILE_LENGTH], int fileNumber) {
    strcpy_s(fileName, FILE_LENGTH, "sub_"); // car tous les fichiers comment par "sub_"
    strcat_s(fileName, FILE_LENGTH, (const char *) fileNumber); // numéro du fichier de 1 à 24
    strcat_s(fileName, FILE_LENGTH, ".csv"); // extension du fichier
}


int getMovement(char path[PATH_NAME_LENGTH]) {
    char movementName[MOVEMENT_LENGTH];
    strncpy_s(movementName, MOVEMENT_LENGTH, path, MOVEMENT_LENGTH); // l'abréviation d'un movement est de 3 caractères
    int iMovement = 0;
    while (iMovement < NUMBER_OF_MOVEMENTS
           && strcmp(movementName, movements[iMovement]) != 0) {
        iMovement++;
    }
    return iMovement;
}

int retrieveGendersBysUsers(int genders[NUMBER_OF_USERS]) {
    FILE *pFiDataSubjectInfos;
    int uselessData;
    int genderRead;

    fopen_s(&pFiDataSubjectInfos, DATA_SUBJECT_FILE, "r");
    if (pFiDataSubjectInfos != NULL) {
        deleteHeader(pFiDataSubjectInfos);
        for (int iUser = 0; !feof(pFiDataSubjectInfos) && iUser < NUMBER_OF_USERS; iUser++) {
            fscanf_s(pFiDataSubjectInfos, "%d,%d,%d,%d,%d\n",
                     &uselessData,
                     &uselessData,
                     &uselessData,
                     &uselessData,
                     &genderRead);
            genders[iUser] = genderRead;
        }

        fclose(pFiDataSubjectInfos);
        return NO_ERROR;
    } else {
        return FILE_OPEN;
    }
}


Data extractVacc(FILE *pPath, Data data) {
    int line;
    double uselessData;
    double VaccX, VaccY, VaccZ;

    deleteHeader(pPath);
    int iData;
    for (iData = 0; !feof(pPath) && iData < NUMBER_OF_VACC_MAX; iData++) {
        fscanf_s(pPath, "%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                 &line,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &uselessData,
                 &VaccX,
                 &VaccY,
                 &VaccZ);

        data.Vacc[iData] = sqrt(pow(VaccX, 2) + pow(VaccY, 2) + pow(VaccZ, 2)); // varAcceleration = racine(x²+y²+z²)
        iData++;
    }

    if (iData < NUMBER_OF_VACC_MAX) {
        /*Si toutes les cellules ne sont pas remplie (moins de 600 Vacc),
         * la cellules suivant la dernière cellule remplie contiendra un '\0'
         * */
        data.Vacc[iData] = '\0';
    }

    return data;
}

void writeDatas(FILE *pFi, Data data) {
    // on va à la ligne car on écrit sur la ligne suivante
    fprintf_s(pFi, "\n");
    // on écrit le mouvement, le genre et l'index
    fprintf_s(pFi, "%d,%d,%d", data.movement, data.gender, data.index);

    for (int iData = 0; !feof(pFi) && iData < NUMBER_OF_VACC_MAX && data.Vacc[iData] != '\0'; iData++) {
        fprintf_s(pFi, ",%lf", data.Vacc[iData]);
    }
}

void deleteHeader(FILE *pFi) {
    char line[LINE_LENGTH];
    fgets(line, sizeof(line), pFi);
}