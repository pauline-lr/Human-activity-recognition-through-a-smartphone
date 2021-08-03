#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_PATHS 15
#define PATH_LENGTH 10
#define NUMBER_OF_FILES 360
#define NUMBER_OF_DATA 600
#define TITLE_LENGTH 50
#define TRAINSET "trainSet.csv"
#define TESTSET "testSet.csv"

void main(void) {
    double paths[NUMBER_OF_PATHS][PATH_LENGTH] = {
            
    };

    FILE *pTrainSetFile;
    fopen(&pTrainSetFile, TRAINSET);
    if (pTrainSetFile) {

        FILE *pTestSetFile;
        fopen(&pTestSetFile, TESTSET);
        if (pTestSetFile) {

            for (int iPath = 0; iPath < NUMBER_OF_PATHS; iPath++) {

                for (int iFile = 0; iFile < NUMBER_OF_FILES; iFile++) {

                    

                }

            }

            fclose(&pTestSetFile);
        } else {
            printf("Impossible d'ouvrir le fichier %s\n", TESTSET);
        }

        fclose(&pTrainSetFile);
    } else {
        printf("Impossible d'ouvrir le fichier %s\n", TRAINSET);
    }
}