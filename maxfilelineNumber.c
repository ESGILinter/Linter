int lineCount(FILE* f){
 
   int count = 0;
   char c;
   rewind(f);     //rembobine le fichier
   if(f == NULL){
       printf("Aucun fichier a compiler");
   }
   else{
       c = fgetc(f);
       while(c != EOF){
           if(c == '\n'){
               count = count + 1;
           }
           c = fgetc(f);
       }
     return count + 1;
   }
}

void maxfilelineNumber(FILE* g,int maxlineNumber){

    if(lineCount(g) > maxlineNumber){
        printf("le nombre de lignes excede celui attendu");
    }
}