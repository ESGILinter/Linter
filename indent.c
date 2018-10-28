#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void indent(FILE* file, int num, char* tab, int taille){

    int i = 0;
    char c;
    int ligne = 1;
    int nbAccolades = 0;
    int nbGuillemets = 0;
    int nbQuotes = 0;
    int nbCharCourant = 0;

    while(i < taille){
        c = fgetc(file);
        tab[i] = c;
        i += 1;
    }

    i = 0;
    while(i < taille){

        if(tab[i] == '\'') nbQuotes +=1;
        if(tab[i] == '"') nbGuillemets +=1;
        if(tab[i] == '{') nbAccolades +=1;
        if(tab[i] == '}' && nbAccolades > 0) nbAccolades -=1;

        if(tab[i] == '{'){
            if(nbQuotes%2 == 0 && nbGuillemets%2 == 0 && rightNumberOfSpaces(tab, nbCharCourant, num, nbAccolades) == 1){
                printf("Erreur '{' a la ligne %d : Nombres d'espaces mauvais pour l'indentatation\n", ligne+1);
            }
        }

        if(tab[i] == '\n'){
			ligne++;
        }

        i+=1;
        nbCharCourant +=1;
    }

}
