#ifndef PROJET_PNDI_IN_C_CONSTANTS_H
#define PROJET_PNDI_IN_C_CONSTANTS_H

#define NB_VACC 600
#define NB_PATH 15
#define PATH_LENGTH 10
#define NB_FILE 24
#define NB_MOVEMENTS 6
#define MOVEMENT_LENGTH 4
#define ACCESS_PATH_LENGTH 256
#define ABRV_MOVEMENT_LENGTH 3
#define HEADER_DATA_LENGTH 150
#define HEADER_LENGTH_VACC 3000
#define HEADER_LENGTH 20000

#define ACCES_PATH "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C_CLion/ressources/"
#define FI_TRAINSET ACCES_PATH "trainSet.csv"
#define PATH ACCES_PATH "A_DeviceMotion_data"
#define FI_TESTSET ACCES_PATH "testSet.csv"
#define FI_DATA_INFO ACCES_PATH "data_subjects_info.csv"
#define FI_MODEL_WOMEN ACCES_PATH "womenModel.csv"
#define FI_MODEL_MEN ACCES_PATH "menModel.csv"
#define FI_MODEL ACCES_PATH "model.csv"


typedef enum codeError;
enum codeError {
    NO_ERROR = 0,
    NO_OPEN_FILE = 1
};

typedef enum gender Gender;
enum gender {
    WOMEN = 0,
    MEN = 1
};

#endif
