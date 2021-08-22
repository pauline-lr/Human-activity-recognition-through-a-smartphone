#include <stdio.h>

#include "Constants.h"
#include "Biblio.h"

int main(void) {
    printf("DEBUT PHASE 1\n");
    int codeErrorPhase1 = creationOfDataSet();

    if (codeErrorPhase1 == NO_ERROR) {
        printf("FIN PHASE 1\n");
        printf("_____________________\n");

        printf("DEBUT PHASE 2 \n");
        int codeErrorPhase2 = creationOfModels();

        if (codeErrorPhase2 == NO_ERROR) {
            printf("FIN PHASE 2 \n");
            printf("_____________________\n");
        }
        else {
            printf("PHASE 2 INTERROMPUE\n");
        }
    }
    else {
        printf("PHASE 1 INTERROMPUE\n");
    }
    return 0;
}