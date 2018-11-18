/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Prototype of parsing.c

*/




int compteLigne(FILE *fichier);
int compteCaractere(FILE *fichier);
char *tableCaractere(FILE *fichier);
char *findFileName(char *path);
int *scoringChar(char *tabChar);
char *ecritMot(char *tabChar, int ind1, int ind2 );
int nombreMot(char *tabChar);
