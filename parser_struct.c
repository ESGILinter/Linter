#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "default.conf"
#define Max_Size 500
#define BORDER "="

struct Rules {
    int max_line_number;
    int max_file_line_number;
    int indent;
    char* array_bracket_eol;
    char* operators_spacing;
    char* coma_spacing;
    char* comments_header;
    char* no_trailing_spaces;
    char* no_multi_declaration;
    char* unused_variable;
    char* undeclared_variable;
    char* unused_function;
    char* no_prototype;
    char* undeclared_function;
    char* variable_assignment_type;
    char* function_parameters_type; 
};
 typedef struct Rules Rules;

struct Configs {
    Rules rules;
    char excludedFiles;
    char extends;
    char recursive;
};
 typedef struct Configs Configs;

struct Configs get_config(char* filename){
      Configs configstruct;
      FILE* fichier = fopen(filename,"r");

      if (fichier != NULL){
          char line[Max_Size];
          int i;
          i = 0;

          while(fgets(line, sizeof(line),fichier) != NULL){
              char* cfline;
              cfline = strstr((char*)line, BORDER);
              cfline = cfline + strlen(BORDER);

              if (i == 3){
                  memcpy(configstruct.rules.array_bracket_eol,cfline,strlen(cfline));
              }else if (i == 4){
                  memcpy(configstruct.rules.operators_spacing,cfline,strlen(cfline));
              }else if (i == 5){
                  memcpy(configstruct.rules.coma_spacing,cfline,strlen(cfline));
              }else if (i == 6){
                  memcpy(configstruct.rules.indent,cfline,strlen(cfline));
              }else if (i == 7){
                  memcpy(configstruct.rules.comments_header,cfline,strlen(cfline));
              }else if (i == 8){
                  memcpy(configstruct.rules.max_line_number,cfline,strlen(cfline));
              }else if (i == 9){
                  memcpy(configstruct.rules.max_file_line_number,cfline,strlen(cfline));
              }else if (i == 10){
                  memcpy(configstruct.rules.no_trailing_spaces,cfline,strlen(cfline));
              }else if (i == 11){
                  memcpy(configstruct.rules.no_multi_declaration,cfline,strlen(cfline));
              }else if (i == 12){
                  memcpy(configstruct.rules.unused_variable,cfline,strlen(cfline));
              }else if (i == 13){
                  memcpy(configstruct.rules.undeclared_variable,cfline,strlen(cfline));
              }else if (i == 14){
                  memcpy(configstruct.rules.unused_function,cfline,strlen(cfline));
              }else if (i == 15){
                  memcpy(configstruct.rules.no_prototype,cfline,strlen(cfline));
              }else if (i == 16){
                  memcpy(configstruct.rules.undeclared_function,cfline,strlen(cfline));
              }else if (i == 17){
                  memcpy(configstruct.rules.variable_assignment_type,cfline,strlen(cfline));
              }else if (i == 18){
                  memcpy(configstruct.rules.function_parameters_type,cfline,strlen(cfline));
              }
              i++;
          }
          fclose(fichier);
      }
    return configstruct;
}

int main(int argc, char** argv){
    
    Configs configstruct;
    configstruct = get_config(FILENAME);

    printf("%s",configstruct.rules.array_bracket_eol);
    printf("%s",configstruct.rules.operators_spacing);
    printf("%s",configstruct.rules.coma_spacing);
    printf("%d",configstruct.rules.indent);
    printf("%s",configstruct.rules.comments_header);
    printf("%d",configstruct.rules.max_line_number);
    printf("%d",configstruct.rules.max_file_line_number);
    printf("%s",configstruct.rules.no_trailing_spaces);
    printf("%s",configstruct.rules.no_multi_declaration);
    printf("%s",configstruct.rules.unused_variable);
    printf("%s",configstruct.rules.undeclared_variable);
    printf("%s",configstruct.rules.unused_function);
    printf("%s",configstruct.rules.no_prototype);
    printf("%s",configstruct.rules.undeclared_function);
    printf("%s",configstruct.rules.variable_assignment_type);
    printf("%s",configstruct.rules.function_parameters_type);

    int maxfilelines;
    int maxlines;
    int ind;
    maxfilelines = atoi(configstruct.rules.max_file_line_number);
    printf("%d\n",maxfilelines);
    maxlines = atoi(configstruct.rules.max_line_number);
    printf("%d\n",maxlines);
    ind = atoi(configstruct.rules.indent);
    printf("%d\n",ind);
}

/*void parsecheck(){
    Configs fichier;
    fichier = fopen("default.conf","r");

    if (fichier != NULL){
    
    }
}*/
