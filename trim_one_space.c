#include <stdio.h>
#include <stdlib.h>
#include "header.h"

char* trim_one_space(char* tab, int size){

    int i, j;
    int cpt = 0;
    i = 0;
    j = 0;

    char* res = malloc(sizeof(char) * size);

    while(i < size){

        if(tab[i] == ' ' && cpt == 0){
            res[j] = tab[i];
            cpt = 1;
            i++;
            j++;
        }
        else if(tab[i] != ' '){
            res[j] = tab[i];
            cpt = 0;
            i++;
            j++;
        }
        else{
            i++;
        }
    }
    res[j-1] = EOF;
    return res;
}
