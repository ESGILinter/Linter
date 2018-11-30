#include <stdio.h>
#include <stdlib.h>

//Retourne le nombre de caractères présents dans le fichier
int char_count(FILE* file){
    char c;
    int nbChar = 0;
    c = fgetc(file);
    while(c != EOF){
        nbChar += 1;
        c = fgetc(file);
    }
    //remise du curseur au début
    fseek(file, 0, SEEK_SET);
    return nbChar;
}

//Retourne le nombre de caractères présents dans le fichier
void copy_file(FILE* file, char* tab){
    char c;
    int cpt = 0;
    c = fgetc(file);
    while(c != EOF){
        tab[cpt] = c;
        cpt += 1;
        c = fgetc(file);
    }
    //remise du curseur au début
    fseek(file, 0, SEEK_SET);
}

//Retourne 0 si il y a autre chose que des espace entre l'accolade et le \n, 1 sinon
int onlySpacesBefore(char* tab, int nbCharCourant){

    //On commence le traitement à partir de la case précedent l'accolade
    int i = nbCharCourant-1;

    while(i >= 0){

        // 9 ascii = TABulation
        if(tab[i] == ' ' || tab[i] == 9){
                i -= 1;
        }

        // 10 ascii = saut de ligne
        else if(tab[i] == 10){
            return 1;
        }

        else{
            return 0;
        }
    }
    return 1;
}

int rightNumberOfSpaces(char* tab, int nbCharCourant, int nbIndent, int nbAcc){

    //On commence le traitement après avoir trouvé l'accolade
    int i = nbCharCourant + 1;
    int spaces = nbIndent * nbAcc;
    int j;

    //Saute les esapces inutiles apres l'accolade
    while(tab[i] == ' '){
        i += 1;
    }
    //Saute les sauts de ligne inutiles apres l'accolade
    while(tab[i] == '\n'){
        i += 1;
    }
    //Vérification si nombre d'esapces correcte
    for(j = 0; j < spaces; j+=1){
        if(tab[i+j] != ' '){
            return 1;
        }
    }
    //Vérification si il n'y a pas d'espace en trop (après le nombre d'espaces requis)
    if(tab[nbCharCourant + spaces + 2] == ' '){
        return 1;
    }

    return 0;
}

//return 1 if line contains char, 0 otherwise
int line_contains_char(char* tab, char c){

    char inc;
    int i = 0;
    inc = tab[i];

    while(inc != EOF && inc != '\n'){
        if(inc == c){

            return 1;
        }
        i++;
        inc = tab[i];
    }
    return 0;
}

int line_number(char* tab){

    int i = 0;
    int cpt = 0;
    char c;
    c = tab[i];

    while(c != EOF){

        if(c == '\n'){
            cpt++;
        }
        i++;
        c = tab[i];
    }
    return cpt;
}

char** copy_lines(char* tab, int nbl){

    char** tab_proto = malloc(sizeof(char*)*nbl);
    int i;
    for(i = 0; i < nbl; i++){
        tab_proto[i] = malloc(sizeof(char)*500);
    }

    char* tab_temp = malloc(sizeof(char*)*500);

    int cpt = 0;
    int j = 0;

    while(cpt < nbl){

        i = 0;
        while(tab[j] != EOF && tab[j] != '\n'){

            tab_temp[i] = tab[j];
            i++;
            j++;
        }
        tab_temp[i] = tab[j];
        j++;
        i = 0;

    if(line_contains_char(tab_temp, '{') == 0 && line_contains_char(tab_temp, '=') == 0 && line_contains_char(tab_temp, '(') == 1 && line_contains_char(tab_temp, ')') == 1 && line_contains_char(tab_temp, ';') == 1){

        while(tab_temp[i] != EOF && tab_temp[i] != '\n'){

            tab_proto[cpt][i] = tab_temp[i];
            i++;
        }
        tab_proto[cpt][i] = tab_temp[i];

    }

    cpt++;

    }

    return tab_proto;
}
