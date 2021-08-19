/*Fonctions utilisées par la phase 1 et 2*/
#include <stdio.h>

#include "header.h"


void deleteHeader(FILE* pFi) {
    char line[LINE_LENGTH];
    fgets(line, sizeof(line), pFi);
}