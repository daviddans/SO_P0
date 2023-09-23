#include "p0_lib.h"
//Funciones auxiliares
int trocearCadena(char * cadena, char * args[])
{ int i=1;
if ((args[0]=strtok(cadena," \n\t"))==NULL)
return 0;
while ((args[i]=strtok(NULL," \n\t"))!=NULL)
i++;
return i;
}


//Funciones vinculadas a comandos de la shell
void exitShell(bool *b){
    printf("Saliendo de la shell ^^");
    *b = false;
    return;
}
void help(char *args){
    if(args==NULL){
        printf("quit exit bye help[cmd]");
    }
    else if(strcmp(args,"help")){
        printf("help muestra una lista de los comandos disponibles\nhelp [comando] muestra una ayuda detallada del comando");
    }
}