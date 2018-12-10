/*fonction permettant de tester la presence de commentaires multilignes
au debut de chaque fichier */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void commentsHeader(char *filePath) {
    int lineNumber = 1;
    int found = 0;

    FILE *f = fopen(filePath, "r");

    if(f == NULL) {
        printf("can't open %s", filePath);
        return;
    }

    while (1) {
        char currentChar = (char) fgetc(f);

        if (currentChar == EOF) {
            break;
        }

        //case in a string or char
        if (currentChar == '"') {
            do {
                currentChar = (char) fgetc(f);
            } while (currentChar != '"');
        } else if (currentChar == '\'') {
            do {
                currentChar = (char) fgetc(f);
            } while (currentChar != '\'');
        }

        if (currentChar == '/' && fgetc(f) == '*' && fgetc(f) == '*') {
            if (lineNumber >= 20) {
                printf("%s : Line %d => multi-line comment need to be in a top of the file.\n", filePath, lineNumber);
                break;
            } else {
                found = 1;
                break;
            }
        } else if (currentChar == '\n') {
            lineNumber += 1;
        }
    }

    fclose(f);
    if (found == 0) {
        printf("%s => need a multi-line comment in the file.\n", filePath);
    }
}