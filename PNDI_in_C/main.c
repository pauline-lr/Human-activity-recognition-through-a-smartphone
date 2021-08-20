#include <stdio.h>

#include "Constantes.h"
#include "Biblio.h"

int main(void) {
    printf("PHASE 1 : Creation of dataset  \n");
    int errPhase1 = creationOfDataSet();

    if (errPhase1 == NO_ERROR) {
        printf("\nPHASE 2 :  Creation of models\n");
        int errPhase2 = creationsOfModels();
        if (errPhase2 != 0) {
            displayError(errPhase2);
        }
    } else {
        displayError(errPhase1);
    }
    return 0;
}

void displayError(int error) {
    switch (error) {
        case NO_ERROR:
            printf("No error\n");
            break;
        case FILE_OPEN:
            printf("ERROR : Open file\n");
            break;
    }
}
