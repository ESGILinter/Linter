/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Function to analyse the role of an expression in a program

*/


#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "Mot_function.h"
#include "test_function.h"


// retourne liste de mots espacés par des espaces

Mot **tabMot(char *tabChar) {

    Mot **tab_mot = malloc(sizeof(Mot*) * nombreMot(tabChar));
    Mot *word = malloc(sizeof(Mot));
    char *mot_compose;
    int *tab_classifie = scoringChar(tabChar);
    int j = 0;
    int h = 0;


    for(int i = 0 ; i < strlen(tabChar) ; i += 1 ) {

        if(tab_classifie[i] == 1 && ((tab_classifie[i-1] == 4 || tab_classifie[i - 1] == 3 || tab_classifie[i - 1] == 2) || i - 1 < 0)) {


            if( j == 0) {

              h = i;
              while(tab_classifie[h] == 1 && h != strlen(tabChar)) {

                    h++;

               }

                mot_compose = ecritMot(tabChar, i , h - 1);
                word = ajouteMot(mot_compose, findLine(tabChar, i), i);
                tab_mot[j] = word;
                j += 1;

            }


            else {

                 h = i;
                 while(tab_classifie[h] == 1 && h != strlen(tabChar)) {

                    h++;
                 }

                 mot_compose = ecritMot(tabChar, i, h - 1);
                 word -> next = ajouteMot(mot_compose, findLine(tabChar, i), i);
                 word = word -> next;
                 tab_mot[j] = word;
                 j += 1;


            }


        }

    }

    return SuppNbTab(tab_mot);

}


// retourne une variable de type Mot

Mot *ajouteMot(char *chai, int line, int position) {

    Mot *word = malloc(sizeof(Mot));
    word -> chaine = chai;
    word -> ligne = line;
    word -> posFirstChar = position;
    word -> next = NULL;

    return(word);
}

// libere la table

void freeTable(Mot *word) {

    if(strcmp(word -> chaine, "NULL"))
        return;

    if( word -> next != NULL) {

        freeTable(word -> next);
    }
    free(word);
}

// compte le un tableau de Mot CREER

int compteOccurence(Mot *word) {

    if(strcmp(word -> chaine, "NULL") == 0)
        return 0;

    int compt = 1;
    while(word -> next != NULL) {

        compt += 1;
        word = word -> next;

    }

    return compt;
}

// supprime les nombres d'un tableau de Mot

Mot **SuppNbTab(Mot **tabMot) {

    int ind = 0;
    int compt = 0;
    char *word;
    int asc = 0;
    int h = 0;

    // nombre de nombres

    for(int i = 0; i < compteOccurence(tabMot[0]); i++) {

        ind = 0;
        word = tabMot[i] -> chaine;
        for(int j = 0; j < strlen(word); j++) {

            asc = word[j];

            if( asc < 47 || asc > 58 ){

                ind = 1;
                break;
            }

        }

        if(ind == 0)
            compt ++;

    }

    // creation nouveau tableau
    Mot** tabMotClean = malloc(sizeof(Mot*) * compteOccurence(tabMot) - compt);
    Mot* motTemp = malloc(sizeof(Mot));

    for(int i = 0; i < compteOccurence(tabMot[0]); i++) {

        ind = 0;
        word = tabMot[i] -> chaine;
        for(int j = 0; j < strlen(word); j++) {

            asc = word[j];

            if( asc < 47 || asc > 58 ){
                ind = 1;
                break;
            }

        }

        if(ind == 1){


            if(h == 0){
                motTemp = ajouteMot(tabMot[i] -> chaine, tabMot[i] -> ligne, tabMot[i] -> posFirstChar);
                tabMotClean[h] = motTemp;
                h ++;
            }
            else{

                motTemp -> next = ajouteMot(tabMot[i] -> chaine, tabMot[i] -> ligne, tabMot[i] -> posFirstChar);
                motTemp = motTemp -> next;
                tabMotClean[h] = motTemp;
                h ++;

            }
        }
    }

    freeTable(tabMot[0]);
    return tabMotClean;

}

// retourne le nombre de structures, union, enumeration appeles

int nbTypeCreated(Mot **tabMot) {


    int compt = 0;
    int indStruct;
    int indUnion;
    int indEnum;

    for(int i = 0 ; i < compteOccurence(tabMot[0]) ; i += 1) {

        indStruct = strcmp(tabMot[i] -> chaine, "struct");
        indUnion = strcmp(tabMot[i] -> chaine, "union");
        indEnum = strcmp(tabMot[i] -> chaine, "enum");

        if(indStruct == 0 || indUnion == 0 || indEnum == 0)  {

            compt += 1;

        }

    }

    return compt;

}

// retourne liste de strucutre

Mot **listTypeCreated(Mot **tabMot){

    if(nbTypeCreated(tabMot) == 0){

        Mot **tabType = malloc(sizeof(Mot*));
        tabType[0] = ajouteMot("NULL", 0, 0);
        return tabType;

    }

    Mot **tabType = malloc(sizeof(Mot*) * nbTypeCreated(tabMot));
    Mot *type = malloc(sizeof(Mot));
    int compt = 0;
    int indStruct = 0;
    int indUnion = 0;
    int indEnum = 0;
    int j = 0;

    if(nbTypeCreated(tabMot) == 0){

        Mot **tabNull = malloc(sizeof(Mot*));
        tabNull[0] = ajouteMot("NULL", 0, 0);
        return tabNull;
    }

    for(int i = 0 ; i < compteOccurence(tabMot[0]) ; i += 1) {

        indStruct = strcmp(tabMot[i] -> chaine, "struct");
        indUnion = strcmp(tabMot[i] -> chaine, "union");
        indEnum = strcmp(tabMot[i] -> chaine, "enum");


        if(indStruct == 0 || indUnion == 0 || indEnum == 0)  {


           if(j == 0) {

                type = ajouteMot(tabMot[i + 1] -> chaine, 0, 0);
                tabType[j] = type;
                j += 1;
           }

           else {

                // si doublon
                compt = 0;
                for(int h = 0 ; h < compteOccurence(tabType[0]) ; h += 1) {

                    if(strcmp(tabType[h] -> chaine, tabMot[i + 1] -> chaine) == 0)
                        compt += 1;
                }

                if(compt == 0) {

                    type -> next = ajouteMot(tabMot[i + 1] -> chaine, 0, 0);
                    type = type -> next;
                    tabType[j] = type;
                    j += 1;

                }

            }
        }

    }

    return tabType;

}

// compte le nombre de variables et fonctions declares

int nbVarFonctDeclar(char *tabChar){

    Mot** tabDeMot = tabMot(tabChar);
    int compt = 0;
    int ind = 0;
    Mot **tabDeType = listTypeCreated(tabDeMot);

    for(int i = 0; i < compteOccurence(tabDeMot[0]); i ++) {

        if(testTypeVarFunct(tabDeMot[i] -> chaine, tabDeType) == 1 && i + 1 < compteOccurence(tabDeMot[0])){

           ind = testTypeVarFunct(tabDeMot[i+1] -> chaine, tabDeType);
           if(ind != 1)
            compt += 1;
        }



    }
    freeTable(tabDeMot);
    return compt;
}


// tableau des noms variables et fonctions déclarées

Mot **tabVarFonctDeclar(char *tabChar) {

    if(nbVarFonctDeclar(tabChar) == 0){

        Mot **tabVF = malloc(sizeof(Mot *));
        tabVF[0] = ajouteMot("NULL", 0, 0);
        return tabVF;

    }

    Mot **tabDeMot = tabMot(tabChar);
    Mot **tabVF = malloc(sizeof(Mot *) * nbVarFonctDeclar(tabChar) );
    Mot *VF = malloc(sizeof(Mot));
    Mot **tabDeType = listTypeCreated(tabDeMot);
    int test = 0;
    int ind = 0;


    for(int i = 0; i < compteOccurence(tabDeMot[0]); i ++) {

        if(testTypeVarFunct(tabDeMot[i] -> chaine, tabDeType) == 1 && i + 1 < compteOccurence(tabDeMot[0])){

           test = testTypeVarFunct(tabDeMot[i+1] -> chaine, tabDeType);
           if(test != 1) {

                if(ind == 0) {

                    VF = ajouteMot(tabDeMot[i + 1] -> chaine, tabDeMot[i + 1] -> ligne, tabDeMot[i + 1] -> posFirstChar);
                    tabVF[ind] = VF;
                    ind ++;

                }

                else {

                    VF -> next = ajouteMot(tabDeMot[i + 1] -> chaine, tabDeMot[i + 1] -> ligne, tabDeMot[i + 1] -> posFirstChar);
                    VF = VF -> next;
                    tabVF[ind] = VF;
                    ind ++;

                }

           }
        }

    }

    freeTable(tabDeMot);
    return tabVF;
}


int nbVariableUsed(char *tabChar) {

    int nb = 0;
    int *tab_classe = scoringChar(tabChar);
    int j = 0;

    for(int i = 0; i < strlen(tabChar) ; i ++) {

        if(testQuote(tabChar, i) != 1){

            if(testCommentaire(tabChar, i) != 1) {

                if (tab_classe[i] == 3){

                    //gauche de l'operateur

                    j = i;
                    while(tabChar[j - 1] == ' ' && j - 1 > 0)
                        j -= 1;

                    if(tab_classe[j - 1] == 1)
                        nb += 1;

                    //droite de l'operateur

                    j = i;

                    while(tabChar[j + 1] == ' ' && j + 1 < strlen(tabChar))
                        j += 1;

                    if(tab_classe[j + 1] == 1){

                        int h = j + 1;
                        while(tab_classe[h + 1] == 1)
                            h ++;

                        // si opération sur fonction
                        while(tabChar[h + 1] == ' ')
                            h += 1;

                        if(tabChar[h + 1] == '('){

                            continue;
                        }

                        else{

                            nb += 1;

                        }

                    }


                }

            }


        }

    }

    return nb;

}


Mot **tabVariableUsed(char *tabChar){

    if(nbVariableUsed(tabChar) == 0){

        Mot **tab_var_used = malloc(sizeof(Mot*));
        tab_var_used[0] = ajouteMot("NULL", 0, 0);
        return tab_var_used;

    }

    int nbVar = nbVariableUsed(tabChar);
    Mot **tab_var_used = malloc(sizeof(Mot*) * nbVar);
    Mot *var_used = malloc(sizeof(Mot));
    int *tab_classe = scoringChar(tabChar);
    int j = 0;
    int h = 0;
    int l = 0;

    for(int i = 0; i < strlen(tabChar) ; i ++) {

        if(testQuote(tabChar, i) != 1){

            if(testCommentaire(tabChar, i) != 1) {

                if (tab_classe[i] == 3){

                    //gauche de l'operateur

                    j = i;
                    while(tabChar[j - 1] == ' ' && j - 1 > 0)
                        j -= 1;

                    if(tab_classe[j - 1] == 1){

                        h = j - 1;
                        while(tab_classe[h - 1] == 1)
                            h -= 1;

                        if(l == 0){

                            var_used = ajouteMot(ecritMot(tabChar, h, j - 1), findLine(tabChar, i), h);
                            tab_var_used[l] = var_used;
                            l += 1;

                        }
                        else{
                            var_used -> next = ajouteMot(ecritMot(tabChar, h, j - 1), findLine(tabChar, i), h);
                            var_used = var_used -> next;
                            tab_var_used[l] = var_used;
                            l += 1;

                        }

                    }


                    //droite de l'operateur

                    j = i;

                    while(tabChar[j + 1] == ' ' && j + 1 < strlen(tabChar))
                        j += 1;

                    if(tab_classe[j + 1] == 1){

                        h = j;
                        while(tab_classe[h + 1] == 1)
                            h += 1;

                        // si opération sur pointeur
                        while(tabChar[h + 1] == ' ')
                            h += 1;

                        if(tabChar[h + 1] == '(')
                            continue;

                        if(l == 0){

                            var_used = ajouteMot(ecritMot(tabChar, j, h + 1), findLine(tabChar, i), j);
                            tab_var_used[l] = var_used;
                            l += 1;

                        }
                        else{

                            var_used -> next = ajouteMot(ecritMot(tabChar, h, j + 1), findLine(tabChar, i), h);
                            var_used = var_used -> next;
                            tab_var_used[l] = var_used;
                            l += 1;

                        }

                    }


                }

            }


        }

    }
    return SuppNbTab(tab_var_used);

}

// rtourne le nombre d'arguments déclarés

int nbArgumentUsed(char *tabChar){

    int nb = 0;
    int *tab_classe = scoringChar(tabChar);
    int j = 0;

    for(int i = 0; i < strlen(tabChar); i ++){

        if(testCommentaire(tabChar, i) == 1 || testQuote(tabChar, i))
            continue;

        if(tabChar[i] == '('){

            j = i + 1;
            while(tabChar[j] == ' ')
                j += 1;

            if(tab_classe[j] == 1 && testQuote(tabChar, j) != 1){

                while(tab_classe[j + 1] == 1 && j + 1 < strlen(tabChar))
                    j += 1;

                // si argument appelé est une fonction
                while(tabChar[j + 1] == ' ' && j + 1 < strlen(tabChar))
                    j += 1;

                if(tabChar[j + 1] == '('){

                        continue;
                }
                else{

                    nb += 1;
                }

            }

        }
        else if(tabChar[i] == ',' && testParenthese(tabChar, i) == 1){

            j = i + 1;
            while(tabChar[j] == ' ')
                j += 1;

            if(tab_classe[j] == 1 && testQuote(tabChar, j) != 1){

                while(tab_classe[j + 1] == 1 && j + 1 < strlen(tabChar))
                    j += 1;

                // si argument appelé est une fonction
                while(tabChar[j + 1] == ' ' && j + 1 < strlen(tabChar))
                    j += 1;

                if(tabChar[j + 1] == '('){

                        continue;
                }
                else{

                    nb += 1;
                }
            }

        }

    }

    return nb;
}

// retorune une liste des variables passées en arguments de fonctions

Mot** tabArgumentUsed(char *tabChar){

    if(nbArgumentUsed(tabChar) == 0){

        Mot **tab_arg = malloc(sizeof(Mot*));
        tab_arg[0] = ajouteMot("NULL", 0, 0);
        return tab_arg;

    }

    int *tab_classe = scoringChar(tabChar);
    Mot** tab_arg = malloc(sizeof(Mot*) * nbArgumentUsed(tabChar));
    Mot* arg = malloc(sizeof(Mot));
    int ind = 0;
    int j = 0;
    int h = 0;

    for(int i = 0; i < strlen(tabChar) ; i ++){

        if(testCommentaire(tabChar, i) == 1 || testQuote(tabChar, i))
            continue;

        if(tabChar[i] == '('){

              j = i + 1;
            while(tabChar[j] == ' ')
                j += 1;

            if(tab_classe[j] == 1 && testQuote(tabChar, j) != 1){

                h = j;
                while(tab_classe[h + 1] == 1)
                    h++;

                // si argument appelé est une fonction
                if(tabChar[h + 1] == '(')
                    continue;


                if(ind == 0){

                    arg = ajouteMot(ecritMot(tabChar, j, h), findLine(tabChar, h), j);
                    tab_arg[ind] = arg;
                    ind += 1;
                }
                else {

                    arg -> next = ajouteMot(ecritMot(tabChar, j, h), findLine(tabChar, h), j);
                    arg = arg -> next;
                    tab_arg[ind] = arg;
                    ind += 1;

                }
            }
        }

        else if(tabChar[i] == ',' && testParenthese(tabChar, i) == 1){

            j = i + 1;
            while(tabChar[j] == ' ')
                j += 1;

            if(tab_classe[j] == 1 && testQuote(tabChar, j) != 1){

                h = j;
                while(tab_classe[h + 1] == 1)
                    h++;

                    if(tabChar[h + 1] == '(')
                        continue;

                    if(ind == 0){

                        arg = ajouteMot(ecritMot(tabChar, j, h), findLine(tabChar, h), j);
                        tab_arg[ind] = arg;
                        ind += 1;

                    }
                    else {

                        arg -> next = ajouteMot(ecritMot(tabChar, j, h), findLine(tabChar, h), j);
                        arg = arg -> next;
                        tab_arg[ind] = arg;
                        ind += 1;

                    }


            }

        }


    }


    return tab_arg;

}


//retorune le nombre de fonctions appelées

int nbFonctUsed(char *tabChar){

    int *tab_classe = scoringChar(tabChar);
    int nbFnct = 0;
    int h = 0;

    for(int i = 0; i < strlen(tabChar); i ++){


        if(testCommentaire(tabChar, i) == 1 || testQuote(tabChar, i) == 1)
            continue;

        if(tabChar[i] == '('){

                h = i;
                while(tabChar[h - 1] == ' ')
                    h -= 1;

                if(tab_classe[h - 1] == 1)
                    nbFnct += 1;


        }


    }

    return nbFnct;

}

// retourne une lste des fonctions appelées

Mot **tabFonctUsed(char *tabChar){

    if(nbFonctUsed(tabChar) == 0){

        Mot **tabFU = malloc(sizeof(Mot*));
        tabFU[0] = ajouteMot("NULL", 0, 0);
        return tabFU;

    }

    Mot **tabFU = malloc(sizeof(Mot*) * nbFonctUsed(tabChar));
    Mot *functUsed = malloc(sizeof(Mot));
    int *tab_classe = scoringChar(tabChar);
    int ind = 0;
    int h = 0;
    int j = 0;

    for(int i = 0; i < strlen(tabChar); i ++){


        if(testCommentaire(tabChar, i) == 1 || testQuote(tabChar, i) == 1)
            continue;

        if(tabChar[i] == '('){

                h = i;
                while(tabChar[h - 1] == ' ')
                    h -= 1;

                if(tab_classe[h - 1] == 1){

                    j = h - 1;
                    while(tab_classe[j - 1] == 1)
                        j -= 1;

                    if(ind == 0){

                        functUsed = ajouteMot(ecritMot(tabChar, j, h - 1), findLine(tabChar, j), j);
                        tabFU[ind] = functUsed;
                        ind += 1;
                    }
                    else{

                        functUsed -> next = ajouteMot(ecritMot(tabChar, j, h - 1), findLine(tabChar, j), j);
                        functUsed = functUsed -> next;
                        tabFU[ind] = functUsed;
                        ind += 1;
                    }

                }


        }


    }


    return tabFU;

}
