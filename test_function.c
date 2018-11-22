/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Different functions to have indication about a charcatere or a word

*/



#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "Mot_function.h"
#include "test_function.h"


// renvoie 1 si le caractere demandé est compris dans des guillements

int testQuote(char *tabChar, int indice) {

    int *tableInd = scoringChar(tabChar);
    int rep = 0;

    // gauche du charactère
    int i = indice - 1;
    while(tabChar[i] != '\n' && i > 0) {

        if(tabChar[i] == '\'' || tabChar[i] == '"') {

            rep = 1;
            break;

        }
        i -= 1;

    }

    // gauche du charactère
    if(rep == 1){

        i = indice + 1;
        while(tabChar[i] != '\n' && i < strlen(tabChar)) {

            if(tabChar[i] == '\'' || tabChar[i] == '"') {
                rep = 1;
                break;
            }

            else {

                rep = 0;
            }
            i += 1;
        }

    }

    return rep;
}


//retourne 1 si l'indice du charactere envoye est dans un commentaire

int testCommentaire(char *tabChar, int indice){

    int j = indice;

    // si le charactere est un ' / '
    if(tabChar[j] == '/'){

        if(tabChar[j + 1] == '*' || tabChar[j + 1] == '/')
            return 1;

        if(j > 0 && (tabChar[j - 1] == '*' || tabChar[j - 1] == '/'))
            return 1;

    }

    // commentaire monoligne

    while(tabChar[j] != '\n' && j > 0){

        if(tabChar[j] == '/' && tabChar[j - 1] == '/')
            return 1;
        j -= 1;
    }

    // commentaire multi lignes

    j = indice;

    while(j > 0){

        if(tabChar[j] == '/' && tabChar[j - 1] == '*')
            return 0;

        else if(tabChar[j] == '*' && tabChar[j - 1] == '/')
            return 1;

        j -= 1;
    }

    return 0;

}

// teste si "" * "" est pour une operation (return 0) ou est un pointeur ( return 1)

int testEtoile(char *tabChar, int indice) {

    int rep = 0;
    int *tableInd = scoringChar(tabChar);
    char *word;
    Mot **tabDeMot = tabMot(tabChar);
    Mot **tabDeTypeCree = listTypeCreated(tabDeMot);
    Mot **tabVFdecl = tabVarFonctDeclar(tabChar);
    int test = 0;
    int i = 0;
    int j = 0;

    if(tabChar[indice] != '*')
        return -1;
    // si declaration de pointeur

    // gauche du pointeur

    i = indice - 1;
    while (tabChar[i] == ' ' && i > 0)
        i -= 1;

    if(tableInd[i] == 1) {

        j = i;
        while(tableInd[i] == 1 && i > 0)
            i -= 1;

        word = ecritMot(tabChar, i + 1, j);
        test = testTypeVarFunct(word, tabDeTypeCree);

    }

    if(test == 1) {

        //droite du pointeur

        i = indice + 1;
        while(tabChar[i] == ' ' && i < strlen(tabChar))
            i ++;

        if(tableInd[i] == 1) {

            j = i;
            while(tableInd[j] == 1 && i < strlen(tabChar))
                j += 1;

        }

        word = ecritMot(tabChar, i, j - 1);
        test = testNameVarFonct(word, tabVFdecl);

        if(test == 1)
            rep = 1;

    }

    // si operation sur pointeur

    if(rep == 0) {
        // lecture a droite de l'etoile
        i = indice + 1;
        test = 0;

        while(tabChar[i] == ' ' && i < strlen(tabChar))
            i ++;

        if(tableInd[i] == 1) {

            j = i;
            while(tableInd[j] == 1 && i < strlen(tabChar))
                j += 1;
                word = ecritMot(tabChar, i, j - 1);
                test = testNameVarFonct(word, tabVFdecl);

        }

        if(test == 1) {

            // lecture a gauche
            i = indice - 1;

            while(tabChar[i] == ' ' && i - 1 > 0)
                i -= 1;

            if(tableInd[i] == 4 || tableInd[i] == 3)
                    rep = 1;

            }

        }


    return rep;

}

// test si le charactère est entre parentheses
int testParenthese(char *tabChar, int indice){

    int rep = 0;
    int j = indice + 1;
    int i = indice - 1;
    //gauche du charactère
    while(i >= 0){

        if(tabChar[i] == '('){

                //droite du charctère
                while(j < strlen(tabChar)){

                    if(tabChar[j] == ')'){
                        rep = 1;
                        break;
                    }
                    j += 1;
                }
                break;
        }
        i -= 1;
    }
    return rep;
}


// retourne 1 si les deux charcatere ont la même portée

int compareStrat(char *tabChar, int indChar1, int indChar2){

    int countStrat = 0;
    int indChange = 0;

    if(indChar1 > indChar2)
        return -1;

    for(int i = indChar2; i >= indChar1 ; i -= 1){

        if(tabChar[i] == '}'){
            countStrat -= 1;
            indChange += 1;
        }

        else if(tabChar[i] == '{'){
            countStrat += 1;
            indChange += 1;
        }

    }

    if( countStrat > 0 || indChange == 0 ){

        return 1;
    }
    else{

        return 0;
    }

}

// retourne 1 si le mot est un type de variable ou de fonction, 0 sinon

int testTypeVarFunct(char* mot, Mot** tabType) {

    int reponse = 0;
    char *tabStand[] = {"char", "int", "long", "short", "double", "float", "void"};

    if(compteOccurence(tabType[0]) != 0){

        for(int i = 0 ; i < compteOccurence(tabType[0]) ; i ++) {
            if(strcmp(tabType[i] -> chaine, mot) == 0)
                reponse = 1;
        }
    }

    for(int j = 0 ; j < 7 ; j ++ ) {

        if(strcmp(tabStand[j], mot) == 0)
            reponse = 1;

    }

    return reponse;
}

// retourne 1 si le mot est le nom d'une variable ou une focntion

int testNameVarFonct(char *mot, Mot** tabVFdec){

    int rep = 0;

    if(compteOccurence(tabVFdec) == 0)
        return 0;

    for(int i = 0; i < compteOccurence(tabVFdec[0]); i += 1) {

        if(strcmp(mot, tabVFdec[i] -> chaine) == 0)
            return 1;

    }

    return 0;
}

// retourne le numero de la ligne de l'index du caratère envoyé

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
