#ifndef HEADER_H
#define HEADER_H

#define NUMBER_OF_PATHS 15
#define PATH_LENGTH 8
#define NUMBER_OF_DATA 600
#define TITLE_LENGTH 50
#define NUMBER_OF_MOVEMENTS 6
#define MOVEMENT_LENGTH 4
#define GENDER_LENGTH 10
#define NUMBER_OF_FILES 24
#define LINE_LENGTH 65
#define DIRECTORY "Ressources/"
#define TRAINSET DIRECTORY"trainSet.csv"
#define TESTSET DIRECTORY"testSet.csv"
#define DATA_SUBJECTS_INFO DIRECTORY"data_subjects_info.csv"

typedef enum error Error;
enum error {
    NO_ERROR,
    FILE_OPEN
};

typedef enum gender Gender;
enum gender {
    FEMME,
    HOMME
};

char fileName[PATH_LENGTH];
Gender genderCode;
char gender[GENDER_LENGTH];
char path[PATH_LENGTH];
int genders[NUMBER_OF_FILES];

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

int readGender(int genders[]);

int getGender(void);

#endif