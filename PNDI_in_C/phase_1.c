#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "header.h"

void creationOfHeader(FILE *pFi);

void fileNameObtention(char fileName[FILE_LENGTH], int fileNumber);

int retrieveGendersBysUsers(int genders[NUMBER_OF_USERS]);

const char *getField(char *line, int num);

int getMovement(char path[PATH_NAME_LENGTH]);

void writeInformations(FILE *pFi, FILE *pPath, int index, int movement, int gender);


int creationOfDataSet(void) {
    /*je récupère d'abord tous les genres que je place dans un tableau
     * afin d'ouvrir le fichier "data_subjects_info.csv" une seule fois*/
    int gendersOfUsers[NUMBER_OF_USERS];
    retrieveGendersBysUsers(gendersOfUsers);


    FILE *pTrainSetFile;
    fopen_s(&pTrainSetFile, TRAINSET, "w+");
    if (pTrainSetFile != NULL) {
        FILE *pTestSetFile;
        fopen_s(&pTestSetFile, TESTSET, "w+");

        if (pTestSetFile != NULL) {
            // créer les entête
            /*Pas dans le DA mais remarque de la prof à ce sujet*/
            creationOfHeader(pTrainSetFile);
            creationOfHeader(pTestSetFile);

            /*à mettre dans la 3ème colonne (cf. structure des fichier test et train
             * dans les consignes)
             * l'index va de 1 à 360 (360 pour NBPATH * NBFILES)*/
            int index = 1;

            for (int iPath = 0; iPath < NUMBER_OF_PATHS; iPath++) {
                char path[PATH_NAME_LENGTH];
                strcpy_s(path, PATH_NAME_LENGTH, paths[iPath]);

                // récupérer le mouvement
                int movement;
                movement = getMovement(path) + 1;

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
                        int genderCode = gendersOfUsers[iFile];
                        int userNumber = iFile + 1;

                        /*Dans les consignes on ne spécifie pas que le genre doit
                         * être écrit en toutes lettres, il est donc plus simple dans
                         * la manipulation des fichiers de garder un système de code
                         * (0 pour femme, 1 pour homme)
                         * donc plus de test sur le genre */


                        // écrire le mouvement, genre et index dans train
                        writeInformations(pTrainSetFile, pFile, index, movement, genderCode);

                        // écrire un test random
                        if (iFile % 5 == 0)
                            writeInformations(pTestSetFile, pFile, index, movement, genderCode);

                    } else {
                        return FILE_OPEN;
                    }

                    index++;
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
    fprintf_s(pFi, "Mouvement, Genre, Index");
    for (int i = 0; i < NUMBER_OF_VACC_MAX; i++)
        fprintf_s(pFi, ",Vacc");
}

void fileNameObtention(char fileName[FILE_LENGTH], int fileNumber) {
    strcpy_s(fileName, FILE_LENGTH, "sub_"); // car tous les fichiers comment par "sub_"
    strcat(fileName, (char) fileNumber); // numéro du fichier de 1 à 24
    strcat(fileName, ".csv"); // extension du fichier
}


int getMovement(char path[PATH_NAME_LENGTH]) {
    char movementName[MOVEMENT_LENGTH];
    strncpy_s(movementName, MOVEMENT_LENGTH, path, MOVEMENT_LENGTH); // l'abréviation d'un movement est de 3 caractères
    int iMovement = 0;
    while (iMovement < NUMBER_OF_MOVEMENTS
           && strcmp(movement, movements[iMovement]) != 0) {
        iMovement++;
    }
    return iMovement;
}

int retrieveGendersBysUsers(int genders[NUMBER_OF_USERS]) {
    FILE *fiDataSubjectInfos;
    char line[LINE_LENGTH];
    int genderRead;

    fopen_s(&fiDataSubjectInfos, path, "r");
    if (fiDataSubjectInfos != NULL) {

        for (int iUser = 0; iUser < NUMBER_OF_USERS; iUser++) {
            fgets(line, LINE_LENGTH, fiDataSubjectInfos);
            genderRead = (int) getField(line, 5);
            genders[iUser] = genderRead;
        }

        fclose(fiDataSubjectInfos);
        return NO_ERROR;
    } else {
        return FILE_OPEN;
    }
}


/*Permet d'accéder à une données précise dans un fichier csv avec
 * le numéro de la ligne et le numéro de la colonne
 * source : https://stackoverflow.com/questions/12911299/read-csv-file-in-c*/
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


void writeInformations(FILE *pFi, FILE *pPath, int index, int movement, int gender) {
    double vAcc;
    char line[LINE_LENGTH_VACC];

    // on va à la ligne car on écrit sur la ligne suivante
    fprintf_s(pFi, "\n");
    // on écrit le mouvement, le genre et l'index
    fprintf_s(pFi, "%d, %d, %d", movement, gender, index);

    /*Il faut maintenant générer les Vacc*/
    for (int iData = 0; !feof(pPath) && iData < NUMBER_OF_VACC_MAX; iData++) {
        fgets(line, LINE_LENGTH_VACC, pPath);
        char VAccX = getField(line, 11); // 11 car vAcc de x se trouve dans la 11ème colonne
        int x = (int) VAccX;

        char VAccY = getField(line, 12);
        int y = (int) VAccY;

        char VAccZ = getField(line, 13);
        int z = (int) VAccZ;

        vAcc = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); // varAcceleration = racine(x²+y²+z²)
        fprintf_s(pFi, ",%f", vAcc);
        iData++;
    }
}