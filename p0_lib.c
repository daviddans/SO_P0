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
void exitShell(bool *term){
    printf("Saliendo de la shell ^^ zZZ");
    *term = true;
    return;
}
