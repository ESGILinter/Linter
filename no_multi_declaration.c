#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void no_multi_declaration(FILE* file, char* tab, int taille){

    int i = 0;
    char c;
    int ligne = 1;
    int nbGuillemets = 0;
    int nbQuotes = 0;
    int nbCharCourant = 0;
    int nbParen = 0;

    while(i < taille){
        c = fgetc(file);
        tab[i] = c;
        if(c == '\'') nbQuotes +=1;
        if(c == '"') nbGuillemets +=1;
        if(c == '(') nbParen +=1;
        if(c == ')' && nbParen > 0) nbParen -=1;

        if(c == ','){
            if(nbQuotes%2 == 0 && nbGuillemets%2 == 0 && nbParen%2 == 0){
                printf("Erreur ',' a la ligne %d : erreur de multi-declaration\n", ligne);
            }
        }
        if(c == '\n') ligne++;

        i+=1;
        nbCharCourant +=1;
    }
}
