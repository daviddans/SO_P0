//Cabecera de las dependencias
//Includes
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

//Funciones vinculadas a los comandos de la shell
void exitShell(bool *term); //salir de la shell
void help(char *args); //imprime una ayuda al usuario
void authors(char *args); //Imprime el nombre y/o login de los autores
void printDate(); //Imprime la fecha del sistema en formato /DD/MM/YYYY
void printTime(); //Imprime la hora del sistema en formato hh:mm:ss
void pid(char *args); //Imprime el pid de la shell actual o padre
void changeDir(char* args); //Muestra la ruta actual o la cambia por la recibida en el parametro args