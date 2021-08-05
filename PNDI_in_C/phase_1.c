#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int creationOfDataSet(void) {
    FILE *pTrainSetFile;
    fopen_s(&pTrainSetFile, TRAINSET, "w+");
    if (pTrainSetFile) {
        FILE *pTestSetFile;
        fopen_s(&pTestSetFile, TESTSET, "w+");
        if (pTestSetFile) {

            // afficher les entêtes des 2 fichiers
            for (int iPath = 0; iPath < NUMBER_OF_PATHS; iPath++) {
                for (int iFile = 0; iFile < NUMBER_OF_FILES; iFile++) {

                    //  récupérer le nom du fichier dans le tableau paths
                    strcpy_s(fileName, PATH_LENGTH, paths[iPath]);
                    int genderCode = iFile + 1;
                    int gender = genders[genderCode - 1];

                    // test genre
                    if (genderCode == FEMME) {
                        strcpy_s(gender, GENDER_LENGTH, "Femme");
                    } else if (genderCode == HOMME) {
                        strcpy_s(gender, GENDER_LENGTH, "Homme");
                    }

                    // écrire path

                    // écrire un etst random

                    //  ouvrir le fichier avec son nom

                    // lire le genre de l'utilisateur en cours

                    int errorGender = readGender(genders);

                    if (gender == 0) {

                    } else {
                        return errorGender;
                    }
                }
            }
            fclose(&pTestSetFile);
        } else {
            return FILE_OPEN;
        }
        fclose(&pTrainSetFile);
        return NO_ERROR;
    } else {
        return FILE_OPEN;
    }
}

int readGender(int genders[]) {
    FILE *fiDataSubjectInfos;
    char line[LINE_LENGTH];
    int genderRead;

    int error = fopen_s(&fiDataSubjectInfos, path, "r");
    if (fiDataSubjectInfos) {

        // supprimer entête
        for (int iUser = 0; iUser < NUMBER_OF_FILES; iUser++) {
            fgets(line, LINE_LENGTH, fiDataSubjectInfos);
            genderRead = getGender();
            genders[iUser] = genderRead;
        }
        fclose(fiDataSubjectInfos);
        return NO_ERROR;
    } else {
        return FILE_OPEN;
    }
}

int getGender(void) {

}