#include <stdio.h>
#include <stdlib.h>
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

    /*int j;
    for(j = 0; j < nbCharTotal; j++){
        printf("%c", res[j]);
    }*/

    int nb_lines = line_number(res);

    char** tab_proto = copy_lines(res, nb_lines);

    int a;
    int b;

    for(a = 0; a < nb_lines; a++){
        b = 0;
        while(tab_proto[a][b] != EOF && tab_proto[a][b] != '\n'){
            printf("%c", tab_proto[a][b]);
            b++;
        }
        printf("%c", tab_proto[a][b]);
        printf("\n");
    }

    //récupérer les prototypes
        //récupérer les lignes sans '{'
        //récupérer les lignes sans '='
        //récupérer les lignes avec '()'
        //récupérer les lignes avec ';'


    //récupérer les fonctions
        //récupérer les lignes avec '{'
        //récupérer les lignes sans '='
        //récupérer les lignes avec '()'

    free(res);

    int i;
    for(i = 0; i < nb_lines; i++){
        free(tab_proto[i]);
    }
    free(tab_proto);

    //indent(file, 4, tab, nbCharTotal);
	//array_backet_eol(file, tab, nbCharTotal);
    //no_multi_declaration(file, tab, nbCharTotal);

	free(tab);
    fclose(file);
    return 0;
}

    //creer une premiere structure :

    /*

    typedef struct Parametre Parametre;
        struct Parametre
        {
            char* type;
            char* name;
            Parametre *suivant;
        };

    typedef struct Liste Liste;
        struct Liste
        {
            Parametre *premier;
        };

    typedef struct Prototype Prototype;
        struct Prototype
        {
            char* type;
            char* function;


        };
    */
