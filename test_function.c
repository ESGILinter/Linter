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

    int rep = 0;

    // gauche du charactère
    int i = indice - 1;
    while(tabChar[i] != '\n' && i >= 0) {

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

    int indNearOpenCur = indChar2;
    while(tabChar[indNearOpenCur - 1] != '{' && indNearOpenCur - 1 > 0 )
        indNearOpenCur -= 1;

    for(int i = indNearOpenCur - 1 ; i >= indChar1 ; i -= 1){

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


// retourne 1 si le chractère envoyé est un indicateur de pointeur

int testPointeur(char *tabChar, int indice){

    int rep = 0;
    int *tab_classe = scoringChar(tabChar);
    Mot **lt_type_cree = listTypeCreated(tabChar);
    int i = indice;
    int countEtoile = 0;


    if(tabChar[indice] != '&' && tabChar[indice] != '*')
        return 0;

    if(testCommentaire(tabChar, indice) == 1 || testQuote(tabChar, indice) == 1)
        return 0;


        // debut de chaine
        while(tabChar[i - 1] == ' ' && i - 1 >= 0)
            i -= 1;
        if(tabChar[i - 1] == '\n' || i - 1 < 0)
            return 1;

        i = indice;
        while(tabChar[i + 1] == ' ' || tabChar[i + 1] == '*')
            i += 1;

        // bitwise and assigment
        if(tabChar[i + 1] == '=' && tabChar[i] == '&')
            return 0;

        // si &&

        if((tabChar[indice - 1] == '&' || tabChar[indice + 1] == '&') && tabChar[indice] == '&')
                    return 0;

        if(tab_classe[i + 1] == 1 || tabChar[ i + 1 ] == '(' ){

            // &
            if(tabChar[indice] == '&'){

                int h = indice;

                while(tabChar[h - 1] == ' ' && h - 1 >= 0)
                    h -= 1;

                if(tab_classe[h - 1] == 3){
                    return 1;
                }
                else{
                    return 0;
                }



            }

            // *

            int h = i + 1;
            while(tabChar[h - 1] == '*' || tabChar[h - 1] == ' '){

                h -= 1;
                if(tabChar[h] == '*')
                    countEtoile += 1;

            }
            // si adresse de pointeur
            if(tabChar[h - 1] == '&' && tabChar[h - 2] != '&')
                return 1;

            // si operation sur pointeut
            if(tab_classe[h - 1] == 3)
                return 1;

            // si déclaration de pointeur
            i = h - 1;
            if(tab_classe[i] == 1){
                while(tab_classe[i - 1] == 1 && i - 1 >= 0)
                    i -= 1;

                if(testTypeVarFunct(ecritMot(tabChar, i, h - 1), lt_type_cree) == 1)
                    return 1;

            }

            // si simple multiplication
            if(countEtoile == 1)
                return 0;

            // si mutiplication sur pointeur
            int g = h;
            while(tabChar[g] != '*')
                g += 1;
            if(g == indice)
                return 0;



    }
    freeTable(lt_type_cree);
    return 1;
}

// retourne 1 si le mot est une est compris dans la syntaxe du C

int testSyntaxe(char *word){

    // non exhaustif
    char *tabSyntaxe[] = {"if", "else", "switch", "while", "for", "malloc", "free", "return", "sizeof"};

    for(int i = 0; i < 9; i += 1){

        if(strcmp(word, tabSyntaxe[i]) == 0){
            return 1;
        }
    }

    return 0;

}
