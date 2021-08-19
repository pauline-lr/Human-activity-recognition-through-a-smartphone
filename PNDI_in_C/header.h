#ifndef HEADER_H
#define HEADER_H

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
#define DIRECTORY "Ressources/"
#define TRAINSET DIRECTORY"trainSet"
#define TESTSET DIRECTORY"testSet"

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

typedef struct data Data;
struct data{
    int movement;
    int gender;
    int index;
    double Vacc[NUMBER_OF_VACC_MAX];
};

char fileName[PATH_LENGTH];
//Gender genderCode;
char path[PATH_LENGTH];
char movement[MOVEMENT_LENGTH];


char paths[NUMBER_OF_PATHS][PATH_LENGTH] = {
        "dws_1", "dws_2", "dws_11",
        "jog_9", "jog_16",
        "sit_5", "sit_13",
        "std_6", "std_14",
        "ups_3", "ups_4", "ups_12",
        "wlk_7", "wlk_8", "wlk_15"
};

// pour gérer les mouvement on initialise un tableau
char movements[NUMBER_OF_MOVEMENTS][MOVEMENT_LENGTH] = {
        "dws", "ups", "jog", "sit", "std", "wlk"
};

void displayError(int error);

int creationOfDataSet(void);

#endif