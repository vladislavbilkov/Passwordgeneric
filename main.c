#include "stdio.h"
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
    printf("Next arguments must be - length pass (max 20 element, min 8 element)\n");
}

void GeneratePass(char *pass, int length, int sizesymvols)
{
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        pass[i] = symvols[rand() % sizesymvols];
    }
}

_Bool CheckParam(int argc, char *argv[]){
    if (argc > 2) {
        printf("Error dont have arguments\n");
        ShowInfoForHelp();
        return 1;
    }
    
    if (strcmp(argv[1], flags[2]) != 0 || strcmp(argv[1], flags[1]) != 0 || strcmp(argv[1], flags[0]) != 0 || strcmp(argv[1], flags[3]) != 0) {
        return 1;
    }


}

int main(int argc, char *argv[]) {
    if(argc == 3) {
        int length = atoi(argv[2]);
        char *pass = malloc(sizeof(char) * (length +1));
        if ((length < 8) || (length > 20)) {
            printf("Bed lenghth\n");
            return 0;
        }
        if(strcmp(argv[1], flags[1]) == 0) {
            GeneratePass(pass, length, SIZEALLSYMVOLS);
            printf("length - %d Password - %s\n", length, pass);
        }
        else if (strcmp(argv[1], flags[2]) == 0) {
            GeneratePass(pass, length, SIZEWITHOUTSPECSYMVOLS);
            printf("length - %d Password - %s\n", length, pass);
        }
        else {
            printf("Dont undersatnd arg\n");
        }
    }
    else if(argc == 2) {
        if (strcmp(argv[1], flags[0]) == 0) {
            ShowInfoForHelp();
        }
        else {
        printf("Dont undertand arg for help use arg (help)\n");
        }
    }
    else {
        printf("You dont use arguments\n");
    }
    return 0;
}