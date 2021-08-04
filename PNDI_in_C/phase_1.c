#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int creationOfDataSet(){
    FILE *pTrainSetFile;
    fopen_s(&pTrainSetFile, TRAINSET, "w");
    if (pTrainSetFile) {

        FILE *pTestSetFile;
        fopen_s(&pTestSetFile, TESTSET, "w");
        if (pTestSetFile) {
            for (int iPath = 0; iPath < NUMBER_OF_PATHS; iPath++) {
                for (int iFile = 0; iFile < NUMBER_OF_FILES; iFile++) {
                    //  récupérer le nom du fichier dans le tableau paths

                    strcpy_s(fileName, PATH_LENGTH, paths[iPath]);

                    //  ouvrir le fichier avec son nom


                    // test genre
                    if(genderCode == FEMME){
                        strcpy_s(gender, GENDER_LENGTH, "Femme");
                    }else if(genderCode == HOMME){
                        strcpy_s(gender, GENDER_LENGTH, "Homme");
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
