#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(){

    FILE *file;

    file = fopen("D:\\Code\\Linter\\file", "r");

    if(file == NULL){

        printf("Erreur lors de l'ouvertue du fichier.\n");
        return 1;
    }

    int nbCharTotal = char_count(file);
	char* tab = malloc(sizeof(char)*nbCharTotal);

    //indent(file, 4, tab, nbCharTotal);
	//array_backet_eol(file, tab, nbCharTotal);
    no_multi_declaration(file, tab, nbCharTotal);

	free(tab);
    fclose(file);
    return 0;
}
