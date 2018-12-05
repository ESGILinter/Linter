#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(){

    FILE *file;

    file = fopen("D:\\Linter\\Linter\\file", "r");

    if(file == NULL){

        printf("Erreur lors de l'ouvertue du fichier.\n");
        return 1;
    }

    int nbCharTotal = char_count(file);
	char* tab = malloc(sizeof(char)*nbCharTotal);

    copy_file(file, tab);

    char* res = trim_one_space(tab, nbCharTotal);

    int* index = malloc(sizeof(int));
    int nb_lines = line_number(res);
    char** tab_proto = copy_lines(res, nb_lines, index);

    int* index2 = malloc(sizeof(int));
    char** tab_proto2 = copy_lines2(res, nb_lines, index2);

    int i, j;
    for(i = 0; i < *index2; i++){
        j = 0;
        while(tab_proto2[i][j] != '('){
            j++;
        }
        if(tab_proto2[i][j-1] == ' ') {
            tab_proto2[i][j-1] = '\0';
        }else{
            tab_proto2[i][j] = '\0';
        }
    }

    for(i = 0; i < *index; i++){
        j = 0;
        while(tab_proto[i][j] != '('){

            j++;
        }

        if(tab_proto[i][j-1] == ' ') {
            tab_proto[i][j-1] = '\0';
        }else{
            tab_proto[i][j] = '\0';
        }
    }

    int check;
    //tab_proto2 = tableau fonctions

    for(i = 0; i < *index2; i++){
        check = 1;
        for(j = 0; j < *index; j++){

            check = strcmp(tab_proto2[i], tab_proto[j]);
            if(check == 0){
                break;
            }
        }
        if(check) printf("Prototype non defini pour la fonction : %s\n", tab_proto2[i]);
    }

    free(res);

    for(i = 0; i < nb_lines; i++){
        free(tab_proto[i]);
    }
    free(tab_proto);

    for(i = 0; i < nb_lines; i++){
        free(tab_proto2[i]);
    }
    free(tab_proto2);

    free(index);
    free(index2);
    //indent(file, 4, tab, nbCharTotal);
	//array_backet_eol(file, tab, nbCharTotal);
    //no_multi_declaration(file, tab, nbCharTotal);

	free(tab);
    fclose(file);
    return 0;
}
