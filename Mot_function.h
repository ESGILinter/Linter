/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Structure of 'Mot' and prototype of different functions about 'Mot'

*/




 struct Mot {

    char *chaine;
    struct Mot *next;
    int posFirstChar;
    int ligne;

    };

    typedef struct Mot Mot;




Mot **tabMot(char *tabChar);

int compteOccurence(Mot *word);

void freeTable(Mot *word);

Mot *ajouteMot(char *chai, int line, int position);

Mot **SuppNbTab(Mot **tabMot);

int nbTypeCreated(char *tabChar);
Mot **listTypeCreated(char *tabChar);

int nbVarDeclar(char *tabChar);
Mot **tabVarDeclar(char *tabChar);

int nbFunctDeclar(char *tabChar);
Mot **tabFunctDeclar(char *tabChar);

int nbVarFonctDeclar(char *tabChar);
Mot **tabVarFonctDeclar(char *tabChar);

int nbVariableUsed(char *tabChar);
Mot **tabVariableUsed(char *tabChar);

int nbArgumentUsed(char *tabChar);
Mot **tabArgumentUsed(char *tabChar);

int nbFonctUsed(char *tabChar);
Mot **tabFonctUsed(char *tabChar);
