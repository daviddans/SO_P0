#include "p0_lib.h"//Fichero con todas las dependencias del codigo

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
//Salir de la Shell
void exitShell(bool *b){
    printf("Saliendo de la shell ^^"); //mensaje de salida
    *b = false; //variable de entrada a falso
    return;
}
//Imprimir mensajes de ayuda de los comandos. Solo se tiene en cuenta el primer parametro de args
void help(char *args){ 
    // Si no recibe argumentos, imprimir una lista de los comandos disponibles
    if(args==NULL)puts("quit exit bye help [cmd] authors [-n|-l]\n");
    //Ayuda sobre el comando help
    else if(strcmp(args,"help") == 0) puts("help muestra una lista de los comandos disponibles\nhelp [comando] muestra una ayuda detallada del comando\n");
    //Ayuda sobre los comandos exit, quit, y bye
    else if(strcmp(args,"quit")==0 || strcmp(args,"exit")==0 || strcmp(args,"bye")==0 ) printf("%s cierra el programa de shell actual\n",args);
    //Ayuda sobre authors
    else if(strcmp(args,"authors")== 0) puts("authors muestra por pantalla nombre y login de los autores\n  authors -l mostrara solo login\n  authors -n mostrara solo nombres\n");
    //Si se introduce un comando no reconocido se mostrara un mensaje de error
    else puts("Error: Comando no reconocido\n");
}
//Imprimir mensajes con los datos de los autores
void authors(char *args){
    char str[190];//String para guardar el mensaje a imprimir
    //Si no tiene argumentos se guardan todos los datos
    if(args == NULL) strcpy(str,"\nAutores:\nNombre del autor 1: David Dans Villares Login del autor 1: david.dans.villares@udc.es\nNombre del autor 2: Pablo Teijeiro Torrón Login del autor 2: pablo.teijeirot@udc.es");
    //El parametro -l guarda solo logins
    else if(strcmp(args,"-l") == 0) strcpy(str,"\nAutores:\nLogin del autor 1: david.dans.villares@udc.es\nLogin del autor 2: pablo.teijeirot@udc.es");
    //El parametro -n guarda solo nombres
    else if(strcmp(args,"-n") == 0) strcpy(str,"\nAutores:\nNombre del autor 1: David Dans Villares\nNombre del autor 2: Pablo Teijeiro Torrón");
    //Si se introduce un parametro no valido se guarda un mensaje de error
    else {
        strcpy(str,"Error: authors no reconoce el parametro: ");
        strcat(str,args);
    }
    printf("%s\n",str);//Imprimir string guardada
}