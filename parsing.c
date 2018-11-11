
Aucun élément sélectionné

Aller au contenu
Utiliser Gmail avec un lecteur d'écran
Cliquez ici pour activer l'affichage des notifications de bureau pour Gmail.   En savoir plus  Masquer
Conversations
0,12 Go (0 %) utilisés sur 15 Go
Gérer
Conditions d'utilisation · Confidentialité · Règlement du programme
Dernière activité sur le compte : Il y a 4 minutes
Détails

﻿#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"

// Fonctions pour parser des fichiers


// Renvoie le nombre de ligne d'un fichier


int compteLigne(FILE* fichier) {

    int compteur = 0;
    char car;
    rewind(fichier);
    car = fgetc(fichier);  //ouverture du fichier necessaire au prealable

    while(car != EOF) {

        if(car == '\n') {

            compteur += 1;

        }

        car = fgetc(fichier);
    }

    rewind(fichier);
    return compteur + 1; //?? why is that
}

// retourne le nombre de caractere du fichier

int compteCaractere(FILE* fichier) {

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

char* tableCaractere(FILE* fichier) {

    rewind(fichier);
    int nb_car = compteCaractere(fichier);
    char* tab = malloc(sizeof(char)*(nb_car));
    char c = fgetc(fichier);
    int i = 1;


    while(c != EOF) {

        tab[i] = c;
        i = i + 1;
        c = fgetc(fichier);

    }

    rewind(fichier);

    return tab;
}

// list un tableau
void printArray(char *array, int size) {

    for (int i = 0; i < size ; i ++) {

        printf("%c", array[i]);
    }

}


// renvoie le numero de la ligne de l'index du caratère envoyer

int findLine(char *tabChar, int indChar) {


    int ligne = 1;

    for (int i = 0 ; i < strlen(tabChar) ; i += 1) {

        if(indChar == i) {
            break;
        }

        if(tabChar[i] == '\n') {
            ligne += 1;
        }

    }


    return ligne;
}

parsing.txt
Affichage de parsingH.txt en cours...
