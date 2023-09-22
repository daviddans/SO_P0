#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Funciones auxiliares
int trocearCadena(char * cadena, char * args[]); //funcion para trocear la entrada

//Funciones vinculadas a los comandos de la shell
void exitShell(bool *term); //salir de la shell
