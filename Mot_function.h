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
int nbTypeCreated(Mot **tabMot);
Mot **listTypeCreated(Mot **tabMot);
int nbVarFonctDeclar(char *tabChar);
Mot **tabVarFonctDeclar(char *tabChar);
Mot **SuppNbTab(Mot **tabMot);
int nbVariableUsed(char *tabChar);
Mot **tabVariableUsed(char *tabChar);
int nbArgumentUsed(char *tabChar);
Mot** tabArgumentUsed(char *tabChar);
