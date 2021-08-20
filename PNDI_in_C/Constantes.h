#ifndef CONSTANTES_H
#define CONSTANTES_H

#define NUMBER_OF_PATHS 15
#define PATH_LENGTH 15
#define PATH_NAME_LENGTH 10
#define LINE_LENGTH 100
#define NUMBER_OF_MOVEMENTS 6
#define MOVEMENT_LENGTH 4
#define NUMBER_OF_FILES 24
#define NUMBER_OF_USERS NUMBER_OF_FILES
#define NUMBER_OF_VACC_MAX 600
#define FILE_LENGTH 15

#define LENGTH_ACCESS_PATH 20
#define DIRECTORY "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/PNDI_in_C/Ressources/"
#define TRAIN_SET_FILE DIRECTORY "trainSet.csv"
#define TEST_SET_FILE DIRECTORY "testSet.csv"
#define MODEL_FILE DIRECTORY "model.csv"
#define MEN_MODEL_FILE DIRECTORY "menModel.csv"
#define WOMEN_MODEL_FILE DIRECTORY "womenModel.csv"
#define DATA_SUBJECT_FILE DIRECTORY "data_subjects_info.csv"

typedef enum error Error;
enum error {
    NO_ERROR,
    FILE_OPEN
};

typedef enum gender Gender;
enum gender {
    FEMME = 0,
    HOMME = 1
};


#endif