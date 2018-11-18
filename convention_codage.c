/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Function of error of Part 1 "Convention codage"

*/

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "Mot_function.h"
#include "test_function.h"
#include "convention_codage.h"

// retourne une rreur si pas d'espace après une virgule

void comma_spacing (char *tabChar,char* nomFich) {

    int ligne = 0;


    for(int i = 0 ; i < strlen(tabChar) ; i += 1) {

        if(tabChar[i] == ',') {

            if(testQuote(tabChar, i) == 1 || testCommentaire(tabChar, i) == 1)
                continue;

            if(tabChar[i + 1] != ' ') {

                ligne = findLine(tabChar, i);
                printf("Error Convention Codage : comma_spacing line %d  in %s\n", ligne, nomFich);
                i += 1;

            }

        }

    }

}


// retourne une erreur si la ligne depasse le nb de caracteres envoyé

void max_line_numbers(char *tabChar, int maxChar, char *nomFich) {

    int compteur = 0;
    int ligne = 0;

    for(int i = 0 ; i < strlen(tabChar) ; i += 1) {

        compteur += 1;

        if(tabChar[i] == '\n' || i == strlen(tabChar) - 1) {

            if(compteur > maxChar) {

                ligne = findLine(tabChar, i);
                printf("Error Convention Codage : max_line_numbers line %d. %d / %d autoriser in %s \n", ligne, compteur, maxChar, nomFich);

            }

            compteur = 0;

        }

    }


}


// retourne une erreur si présence d'espace en fin de ligne

void no_trailing_space(char *tabChar, char *nomFich) {

    int j = 0;
    int compt = 0;
    int ligne = 0;

    for (int i = 0 ; i < strlen(tabChar) ; i += 1) {

        if(testCommentaire(tabChar, i) == 1 || testQuote(tabChar, i) == 1)
            continue;

        compt = 0;

        if(tabChar[i] == '\n' || i == strlen(tabChar) - 1) {

            j = i - 1;
            while(tabChar[j] != '\n' && i != j) {

                if(tabChar[j] != ' ') {
                    break;
                }
                j  -= 1;
                compt += 1;
            }

        if(compt != 0) {

            ligne = findLine(tabChar, i);
            printf("Error Convention Codage : no-trailing-space line %d in %s.\n", ligne, nomFich );

            }

        }

    }

}

// retourne une erreur si pas d'espaces de chaque cote d'un operateur

void operator_spacing(char *tabChar, char *nomFich) {

    int *tableInd = scoringChar(tabChar);
    int ligne = 0;

    for(int i = 0; i < strlen(tabChar); i += 1) {

        ligne = findLine(tabChar, i);
        if(tableInd[i] == 3) {

            if(testQuote(tabChar, i) != 1) {

                    if(testCommentaire(tabChar, i) != 1 ) {


                        if(tabChar[i] == '*') {

                            if(testEtoile(tabChar, i) == 1)
                                continue;
                        }


                        if( (!(tabChar[i + 1] == ' ' || tableInd[i + 1] == 3) || !(tabChar[i - 1] == ' ' || tableInd[i - 1] == 3)) )
                                printf("Error convention codage, operator_spacing line %d in file %s \n", ligne, nomFich);


                    }

            }

        }

    }

}




