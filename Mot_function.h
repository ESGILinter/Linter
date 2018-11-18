/*

** FILENAME : Linter

** MADE BY : Ilès Benkoussa, Arnauld Biam, Victor Meyer

** Structure of 'Mot' and prototype of different functions about 'Mot'

*/




 struct Mot {

    char *chaine;
    struct Mot* next;
    int strat;
    int ligne;

    };

    typedef struct Mot Mot;




Mot **tabMot(char *tabChar, int nb_char);
int compteOccurence(Mot *word);
void freeTable(Mot *word);
Mot *ajouteMot(char *chai, int line, int indent);
int nbTypeCreated(Mot **tabMot);
Mot **listTypeCreated(Mot **tabMot);
int nbVarFonctDeclar(Mot **TabMot);
Mot **tabVarFonctDeclar(Mot **tabMot);
Mot **SuppNbTab(Mot **tabMot);
int nbVariableUsed(char *tabChar);
Mot **tabVariableUsed(char *tabChar);
int nbArgumentUsed(char *tabChar);
Mot** tabArgumentUsed(char *tabChar);
