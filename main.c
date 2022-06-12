#include "stdio.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char *flags[] = {"help", "-sl", "-nsl", "show"};
const int SIZEALLSYMVOLS = 89;
const int SIZEWITHOUTSPECSYMVOLS = 62;

const char symvols[] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 
                        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M',
                        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '!', '@', '#', '$', '%', '&', '*', '(', ')', '_', '^', '+', '=', '-', '[', ']',
                        '{', '}', ';', ':', '/', '?', '.', ',', '|', '`', '~'};

enum command{
    sl = 2,
    nsl = 3,
    help = 4,
    show_all = 5,
    show_el = 6
};

void ShowInfoForHelp() {
    printf("For generate password please use this argiments:\n");
    printf("First arguments must be - special literals('-sl' use, '-nsl' not use)\n ");
    printf("Next arguments must be - size pass (max 20 element, min 8 element)\n");
}

void GeneratePass(char *pass, int size, int sizesymvols)
{
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        pass[i] = symvols[rand() % sizesymvols];
    }
}

_Bool CheckParam(int argc, char *argv[]){
    if (argc < 2) {
        printf("Error, dont have arguments\n");
        ShowInfoForHelp();
        return 0;
    }
    
    int tmp = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(argv[1], flags[i])) {
            tmp++;
        }
    }

    if (tmp == 0) {
        printf("Error, unvalid first argument\n");
        printf("Please use this first arguments - ");
        for (int i = 0; i < 4; i++) {
            printf(" ,%s", flags[i]);
        }
        return 0;
    }
    if (argc == 3) {
        int size = atoi(argv[2]);
        if (size < 8 || size > 20) {
            printf("Error, unvalid lenght password");
            return 0;
        }
    }
    return 1;
}

_Bool AskNewPass(){
    char inputel[4] = "";
    printf("Generate next pass? (yes/no) ");
    scanf("%s", inputel);
    if(inputel[0] == 'y') {
        return 1;
    }else {
        return 0;
    }    
}

_Bool AskToSave() {
    char inputel[4] = "";
    printf("Save password? (yes/no) ");
    scanf("%s", inputel);
    if(inputel[0] == 'y') {
        return 1;
    }else {
        return 0;
    }    
}

struct DataToWrite {
    char Password[21];
    char Name[21]; 
};

void WriteDataToFile(struct DataToWrite data) {
    FILE *outfile;
    outfile = fopen("data/data.dat", "w");
    fwrite(&data, sizeof(struct DataToWrite), 1, outfile);
    fclose(outfile);
}

void LoadDataFromFile() {
    FILE *infile;
    infile  = fopen("data/data.dat", "r");
    struct DataToWrite data;
    while (fread(&data, sizeof(struct DataToWrite), 1, infile)) {
        printf("Teg - %s, Password - %s", data.Name, data.Password);
    }
    fclose(infile);
}

void LoadDataKeyFromFile(char *teg) {
    FILE *infile;
    infile  = fopen("data/data.dat", "r");
    struct DataToWrite data;
    while (fread(&data, sizeof(struct DataToWrite), 1, infile)) {
        if (strcmp(data.Name,teg) == 0) {
            printf("Teg - %s, Password - %s", data.Name, data.Password);
            break;    
        }
    }
    fclose(infile);
}

int main(int argc, char *argv[]) {
    if(CheckParam(argc, argv) == 0) {
        return 0;
    }
    
    //generate pass
    if(strcmp(argv[1], flags[1]) == 0 || strcmp(argv[1], flags[2]) == 0) {
        int size = atoi(argv[2]);
        char *pass = malloc(sizeof(char) * (size + 1));
        if(strcmp(argv[1], flags[1]) == 0) {
            GeneratePass(pass, size, SIZEALLSYMVOLS);
            printf("Password - %s\n",pass);
            while(AskNewPass()) {
                GeneratePass(pass, size, SIZEALLSYMVOLS);
                printf("Password - %s\n",pass);
            }
        }
        else if (strcmp(argv[1], flags[2]) == 0) {
            GeneratePass(pass, size, SIZEWITHOUTSPECSYMVOLS);
            printf("Password - %s\n",pass);
            while(AskNewPass()) {
                GeneratePass(pass, size, SIZEWITHOUTSPECSYMVOLS);
                printf("Password - %s\n",pass);
            }
        }
        //save pass
        if (AskToSave()) {
            char inputname[21] = "";
            printf("Input teg to save - ");
            scanf("%s", inputname);
            struct DataToWrite Data;
            strcpy(Data.Password, pass);
            strcpy(Data.Name, inputname);
            WriteDataToFile(Data);
            printf("Saved");
        }
        return 0;
    }
    //show passwords
    if(strcmp(argv[1], flags[3]) == 0) {
        printf("conch\n");
        int size = 10;
        LoadDataFromFile();
        printf("you\n");
        
        return 0;
    }
    //help
    if (strcmp(argv[1], flags[0]) == 0) {
        ShowInfoForHelp();
    }
    return 0;
}