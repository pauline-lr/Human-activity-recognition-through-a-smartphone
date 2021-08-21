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

#define FI_TRAINSET "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/trainSet.csv"
#define PATH "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/A_DeviceMotion_data"
#define FI_TESTSET "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/testSet.csv"
#define FI_DATA_INFO "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/data_subjects_info.csv"
#define FI_MODEL_WOMEN "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/womenModel.csv"
#define FI_MODEL_MEN "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/menModel.csv"
#define FI_MODEL "D:/IG 2020-2021/Q3/Projet PNDI AOUT 2021/Projet_PNDI_in_C/ressources/model.csv"
#define HEADER_LENGTH 20000



typedef enum codeError;
enum codeError{
    NO_ERROR = 0,
    NO_OPEN_FILE = 1
};

typedef enum gender Gender;
enum gender {
    WOMEN = 0,
    MEN = 1
};

#endif
