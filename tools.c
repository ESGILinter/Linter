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
