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

typedef struct movement Movement;
struct movement {
    int move;
    int gender;
    double xAcceleration;
    double yAcceleration;
    double zAcceleration;
};

void main(void) {
    double paths[NUMBER_OF_PATHS][PATH_LENGTH];

    // open file "trainSet.csv"

    // open file "testSet.csv"

    for (int iPath = 0; iPath < NUMBER_OF_PATHS; iPath++) {

        // movement = abréviation des 3 premiers caractères du répertoire

        for (int iFile = 0; iFile < NUMBER_OF_FILES; iFile++) {

            // récupérer le nom du fichier dans le tableau paths

            // ouvrir le fichier avec son nom

            if (/* le fichier ne s'est pas ouvert */) {

                // écrire movement et gender dans "trainSet.csv"

                // ident = numéro du movement (1 à 360)

                // open file "data_subjects_info.csv"

                // récupérer le code de la personne avec le nom de chaque fichier

                // genderCode = rechercher la ligne associée au code personne et extraire le numéro de son genre

                switch (genderCode) {
                    case 0:
                        gender = "Femme";
                        break;
                    case 1:
                        gender = "Homme";
                }

                // close file "data_subjects_info.csv"

                for (int iData = 0; iData < NUMBER_OF_DATA; iData++) {

                    // récupérérer acceleration.x

                    // x = acceleration.x

                    // récupérérer acceleration.y

                    // y = acceleration.y

                    // récupérérer acceleration.z

                    // z = acceleration.z

                    // varAcceleration = racine(x²+y²+z²)

                    // éventuellement écrire cet enregistrement dans "testSet.csv" (aléatoire)

                }

                // écrire varAcceleration dans "trainSet.csv"

            }

            // fermer le fichier avec son nom

        }

    }

    // close file "trainSet.csv"

    // close file "testSet.csv"

}

void openFile(char fileName[]) {
    FILE *pFile;
    Movement movement;
    char title [TITLE_LENGTH];

    fopen(&pFile, fileName);

    if (pFile) {
        printf("%s\n", fgets(title, TITLE_LENGTH, pFile));
    } else {
        printf("Impossible d'ouvrir le fichier\n");
    }

}