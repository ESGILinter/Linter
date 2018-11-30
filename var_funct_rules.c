/*

** FILENAME : Linter

** MADE BY : Ilès Benkousa, Arnauld Biam, Victor Meyer

** Differents functions to alert of no respect variables or functions rules

*/

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "Mot_function.h"
#include "test_function.h"
#include "convention_codage.h"
#include "var_funct_rules.h"



//  retourne un message d'erreur si appel à une variable non déclarée

void undeclared_variable(char *tabChar, char *nomFich){


    Mot** tabVFdecl = tabVarFonctDeclar(tabChar);
    Mot** tabVarUsed = tabVariableUsed(tabChar);
    Mot** tabArgUsed = tabArgumentUsed(tabChar);
    int indPresence = 0;
    int indStrat = 0;

    // pour les variables appelées

    for(int i = 0; i < compteOccurence(tabVarUsed[0]) ; i ++){

        indPresence = 0;
        indStrat = 0;


        for(int j = 0; j < compteOccurence(tabVFdecl[0]) ; j ++){


            if(strcmp(tabVarUsed[i] -> chaine, tabVFdecl[j] -> chaine) == 0) {
                    indPresence = 1;

                if(compareStrat(tabChar, tabVFdecl[j] -> posFirstChar, tabVarUsed[i] -> posFirstChar) == 0)
                    indStrat = 1;


            }



        }

        if(indPresence == 0 || indStrat == 1){
            printf("Error Variables and Functions rules, undeclared_variable line %d in file : %s \n", tabVarUsed[i] -> ligne, nomFich);
        }

    }

    // pour les arguments appelés

    for(int i = 0; i < compteOccurence(tabArgUsed[0]) ; i ++){

        indPresence = 0;
        indStrat = 0;


        for(int j = 0; j < compteOccurence(tabVFdecl[0]) ; j ++){


            if(strcmp(tabArgUsed[i] -> chaine, tabVFdecl[j] -> chaine) == 0) {
                    indPresence = 1;

                if(compareStrat(tabChar, tabVFdecl[j] -> posFirstChar, tabArgUsed[i] -> posFirstChar) == 0)
                    indStrat = 1;


            }



        }

        if(indPresence == 0 || indStrat == 1){
            printf("Error Variables and Functions rules, undeclared_variable line %d in file : %s \n", tabArgUsed[i] -> ligne, nomFich);
        }

    }

    freeTable(tabVarUsed);
    freeTable(tabVFdecl);
    freeTable(tabArgUsed);


}

