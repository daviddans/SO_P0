#include <stdio.h>
#include <stdbool.h>
#include <string.h>


//Funciones auxiliares

//Funciones vinculadas a los comandos de la shell
void exitShell(bool *term); //salir de la shell
void help(char * args); //imprime una ayuda al usuario