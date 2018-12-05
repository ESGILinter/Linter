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


    Mot** tabVdecl = tabVarDeclar(tabChar);
    Mot** tabVarUsed = tabVariableUsed(tabChar);
    Mot** tabArgUsed = tabArgumentUsed(tabChar);

    int indPresence = 0;
    int indStrat = 0;

    // pour les variables appelées

    for(int i = 0; i < compteOccurence(tabVarUsed[0]) ; i ++){

        indPresence = 0;
        indStrat = 0;

        if(compteOccurence(tabVdecl[0]) == 0){
            indStrat == 1;
        }

        for(int j = 0; j < compteOccurence(tabVdecl[0]) ; j ++){


            if(strcmp(tabVarUsed[i] -> chaine, tabVdecl[j] -> chaine) == 0) {
                    indPresence = 1;

                if(compareStrat(tabChar, tabVdecl[j] -> posFirstChar, tabVarUsed[i] -> posFirstChar) == 0)
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


        for(int j = 0; j < compteOccurence(tabVdecl[0]) ; j ++){


            if(strcmp(tabArgUsed[i] -> chaine, tabVdecl[j] -> chaine) == 0) {
                    indPresence = 1;

                if(compareStrat(tabChar, tabVdecl[j] -> posFirstChar, tabArgUsed[i] -> posFirstChar) == 0)
                    indStrat = 1;


            }



        }

        if(indPresence == 0 || indStrat == 1){
            printf("Error Variables and Functions rules, undeclared_variable line %d in file : %s \n", tabArgUsed[i] -> ligne, nomFich);
        }

    }

    freeTable(tabVarUsed);
    freeTable(tabVdecl);
    freeTable(tabArgUsed);


}


// retourne une erreure si appel à une fonction déclarée

void undeclared_function(char *tabChar, char *nomFich){


    Mot **tab_funct_declar = tabFunctDeclar(tabChar);
    Mot **tab_funct_used = tabFonctUsed(tabChar);
    int indPresence = 0;
    int indStrat = 0;

    if(nbFonctUsed(tabChar) == 0)
        return;


    for(int i = 0; i < compteOccurence(tab_funct_used[0]); i ++){


        indPresence = 0;
        indStrat = 0;

        if(nbFonctUsed(tabChar) == 0)
            return;

        for(int j = 0; j < compteOccurence(tab_funct_declar[0]); j ++) {


            if(strcmp(tab_funct_used[i] ->chaine, tab_funct_declar[j] -> chaine) == 0){
                indPresence = 1;

                if(compareStrat(tabChar, tab_funct_declar[j] -> posFirstChar, tab_funct_used[i] -> posFirstChar ) == 0){

                        indStrat = 1;
                        break;
                }

            }


        }

         if(indPresence == 0 || indStrat == 1)
                printf("Error Variables and Functions rules, undeclared_function line %d in file : %s \n", tab_funct_used[i] -> ligne, nomFich);

    }

    freeTable(tab_funct_declar[0]);
    freeTable(tab_funct_used[0]);

}

// retorune une erreure si une variable est déclaréee mais non utilisé

void unsed_variable(char *tabChar, char *nomFich){

    Mot **tab_var_used = tabVariableUsed(tabChar);
    Mot **tab_arg_used = tabArgumentUsed(tabChar);
    Mot **tab_var_decl = tabVarDeclar(tabChar);
    int indPresence = 0;
    int indStrat = 0;


    if(compteOccurence(tab_var_decl[0]) == 0)
        return;

    for(int i = 0; i < compteOccurence(tab_var_decl[0]); i ++){

        indPresence = 0;
        indStrat = 0;

        for(int j = 0; j < compteOccurence(tab_var_used[0]); j ++){

            if(strcmp(tab_var_used[j] -> chaine, tab_var_decl[i] -> chaine) == 0) {
                    indPresence = 1;

                if(compareStrat(tabChar, tab_var_decl[i] -> posFirstChar, tab_var_used[j] -> posFirstChar) == 0)
                    indStrat = 1;


            }

        }


        for(int h = 0; h < compteOccurence(tab_arg_used[0]); h ++){

                if(strcmp(tab_arg_used[h] -> chaine, tab_var_decl[i] -> chaine) == 0) {
                        indPresence = 1;

                    if(compareStrat(tabChar, tab_var_decl[i] -> posFirstChar, tab_arg_used[h] -> posFirstChar) == 0)
                        indStrat = 1;


                }

            }

      if(indPresence == 0 || indStrat == 1)
            printf("Error Variables and Functions rules, unsed_variable line %d in file : %s \n", tab_var_decl[i] -> ligne, nomFich);

    }

    freeTable(tab_arg_used[0]);
    freeTable(tab_var_used[0]);
    freeTable(tab_var_decl[0]);

}

// retourne une erreur si declaration d'une fonction non utilisé

void unsed_function(char *tabChar, char *nomFich){

    Mot **tab_function_decl = tabFunctDeclar(tabChar);
    Mot **tab_function_used = tabFonctUsed(tabChar);
    int indPresence = 0;
    int indStrat = 0;

    if(nbFunctDeclar(tabChar) == 0)
        return;

    for(int i = 0; i < compteOccurence(tab_function_decl[0]); i += 1){

        indPresence = 0;
        indStrat = 0;

        if(nbFonctUsed(tabChar) == 0)
            return;

        for(int j = 0; j < compteOccurence(tab_function_used[0]); j += 1){


            if(strcmp(tab_function_decl[i] -> chaine, tab_function_used[j] -> chaine) == 0)
                indPresence = 1;

            if(compareStrat(tabChar, tab_function_decl[i] -> posFirstChar, tab_function_used[j] -> posFirstChar) == 0)
                indStrat = 1;


        }

        if(indPresence == 0 || indStrat == 1)
                printf("Error Variable and Function rules, unsed_function line %d in file : %s \n", tab_function_decl[i] -> ligne, nomFich);



    }

    freeTable(tab_function_decl[0]);
    freeTable(tab_function_used[0]);


}
