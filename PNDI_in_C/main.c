//
// Created by Pauline on 04/08/2021.
//
#include <stdio.h>
#include "header.h"


void main(void){
    int error;

    printf("PHASE 1 : Creation of dataset  \n");
    // appel à la phase 1
    int errPhase1 = creationOfDataSet();/*code erreur phase 1*/

    if(errPhase1 == 0){
        printf("\nPHASE 2 :  Creation of models\n");
        int errPhase2 = ;/*code erreur phase 2*/
        if(errPhase2 == 0){
            printf("\nPHASE 3 :  Evaluation of models\n");
            int errPhase3 = ;/*code erreur phase 3*/
            if(errPhase3 == 0){
                // afficher le résultat de phase 3
            }else{
                displayError(errPhase3);
            }
        }else{
            displayError(errPhase2);
        }
    }else{
        displayError(errPhase1);
    }
}

void displayError(int error){
    switch (error) {
        case 0:
            printf("Not error\n");
            break;
        case 1 :
            printf("ERROR : Open file\n");
            break;
        case 2 :
            break;
    }
}
