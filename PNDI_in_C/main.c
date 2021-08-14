#include <stdio.h>

#include "header.h"

int main(void) {
    int error;

    printf("PHASE 1 : Creation of dataset  \n");
    // appel à la phase 1
    int errPhase1 = creationOfDataSet();/*code erreur phase 1*/

    if (errPhase1 == 0) {
        printf("\nPHASE 2 :  Creation of models\n");
        /*//int errPhase2 = ; //code erreur phase 2
        if (errPhase2 != 0) {
            displayError(errPhase2);
        }*/
    } else {
        displayError(errPhase1);
    }
    return 0;
}

void displayError(int error) {
    switch (error) {
        case 0:
            printf("No error\n");
            break;
        case 1:
            printf("ERROR : Open file\n");
            break;
        case 2:
            break;
    }
}
