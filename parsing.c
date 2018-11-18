/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Function to analyse the file

*/


#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "Mot_function.h"
#include "test_function.h"



// Renvoie le nombre de ligne d'un fichier


int compteLigne(FILE *fichier) {

    int compteur = 0;
    char car;
    rewind(fichier);
    car = fgetc(fichier);

    while(car != EOF) {

        if(car == '\n') {

            compteur += 1;

        }

        car = fgetc(fichier);

    }

    rewind(fichier);
    return compteur + 1;

}

// retourne le nombre de caractere du fichier

int compteCaractere(FILE *fichier) {

    int compteur = 0;
    char car;
    rewind(fichier);
    car = fgetc(fichier);

    while(car != EOF) {

        compteur += 1;
        car = fgetc(fichier);
    }

    rewind(fichier);
    return compteur;

}

// Retourne un tableau des caractères du fichier envoyé

char *tableCaractere(FILE *fichier) {

    rewind(fichier);
    int nb_car = compteCaractere(fichier);
    char *tab = malloc(sizeof(char) * nb_car);
    char c = fgetc(fichier);
    int i = 0;

    while(c != EOF) {

        tab[i] = c;
        i = i + 1;
        c = fgetc(fichier);

    }

    rewind(fichier);

    return tab;
}

// retourne le nom du fichier du lien envoyé

char *findFileName(char *path) {

    int i = strlen(path) - 1;
    int longNom = 0;

    for(i ; i >= 0 ; i--) {

        if(path[i] == '/') {
            break;
        }

    }

    longNom = strlen(path) - i - 1;
    char *nomFichier = malloc(sizeof(char) * (longNom + 1));

    for(i = 0 ; i < longNom ; i++) {

        nomFichier[i] = path[i + strlen(path) - longNom];

    }

    nomFichier[i] = '\0';

    return nomFichier;

}


// retourne tableau de classification des charactères

int *scoringChar(char *tabChar) {

    int *tabClassifie = malloc(sizeof(int) * strlen(tabChar));

    for(int i = 0 ; i < strlen(tabChar) ; i ++) {

        // si le caractère est un alphanumerique ind == 1

        if( (tabChar[i] > 47 && tabChar[i] < 58) || (tabChar[i] > 64 && tabChar[i] < 91) || (tabChar[i] < 123 && tabChar[i] > 96 || tabChar[i] == '_') )
            tabClassifie[i] = 1;

        // si le caractère est un contenant

        else if ( tabChar[i] == '[' || tabChar[i] == ']'|| tabChar[i] == '{' || tabChar[i] == '}' || tabChar[i] == '(' || tabChar[i] == ')' )
            tabClassifie[i] = 2;

        // si le caratère est un operateur ind = 3

        else if ( tabChar[i] == '?' || tabChar[i] == '.' || tabChar[i] == ':' || tabChar[i] == '/' || tabChar[i] == '!' || tabChar[i] == '*' || tabChar[i] == '%' || tabChar[i] == '+' || tabChar[i] == '=' || tabChar[i] == '-' || tabChar[i] == '~' || tabChar[i] == '$' || tabChar[i] == '&' || tabChar[i] == '|' || tabChar[i] == '^' || tabChar[i] == '<' || tabChar[i] == '>' )
            tabClassifie[i] = 3;

        // si charactère fin de chaine ind = 4

        else if ( tabChar[i] == ';' || tabChar[i] == '\n' || tabChar[i] == ' ')
            tabClassifie[i] = 4;


        // guillemets ou apostrophes

        else if ( tabChar[i] == '\'' || tabChar[i] == '"' )
            tabClassifie[i] = 5;

        else {

            tabClassifie[i] = 0;

        }


 }

 return tabClassifie;


}


// retourne un mot entre 2 indices d'un tableau donnés

char *ecritMot(char *tabChar, int ind1, int ind2 ) {

    int lenMot = ind2 - ind1 + 1;
    int j = 0;
    char *mot = malloc(sizeof(char)*lenMot);

    for(int i = ind1 ; i <= ind2 ; i ++) {

        mot[j] = tabChar[i];
        j += 1;
    }
    mot[j] = '\0';

    return mot;

}



// reourne nombre de mots d'un FICHIER .C

int nombreMot(char *tabChar) {

    int *tb_classe;
    tb_classe = scoringChar(tabChar);
    int compt = 0;

    for(int i = 0 ; i < strlen(tabChar) ; i++) {

        if(tb_classe[i] == 1 && (tb_classe[i-1] == 4 || tb_classe[i - 1] == 3 || tb_classe[i - 1] == 2 || i - 1 < 0 )) {

            compt += 1;
        }

    }

    return compt;
}
