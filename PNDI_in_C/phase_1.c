#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_PATHS 15
#define PATH_LENGTH 8
#define NUMBER_OF_FILES 360
#define NUMBER_OF_DATA 600
#define TITLE_LENGTH 50
#define NB_MOVEMENTS 6
#define MOVEMENT_LENGTH 4
#define GENDER_LENGTH 10
#define TRAINSET "trainSet.csv"
#define TESTSET "testSet.csv"

typedef  enum gender Gender;
enum gender {
    FEMME,
    HOMME
};

void main(void) {
    char fileName[PATH_LENGTH];
    int genderCode;
    char gender[GENDER_LENGTH];

    char paths[NUMBER_OF_PATHS][PATH_LENGTH] = {
            "dws_1/", "dws_2/", "dws_11/",
            "jog_9/", "jog_16/",
            "sit_5/", "sit_13/",
            "std_6/", "std_14/",
            "ups_3/", "ups_4/", "ups_12/",
            "wlk_7/", "wlk_8/", "wlk_15/"
    };

    // pour gérer les mouvement on initialise un tableau
    char movements[NB_MOVEMENTS][MOVEMENT_LENGTH] = {
            "dws", "ups", "jog", "sit", "std", "wlk"
    };

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
            printf("Impossible d'ouvrir le fichier %s\n", TESTSET);
        }

        fclose(&pTrainSetFile);
    } else {
        printf("Impossible d'ouvrir le fichier %s\n", TRAINSET);
    }
}