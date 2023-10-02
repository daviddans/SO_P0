//Cabecera con las funciones de la practica 0
#include "lista.h" // Cabecera con la implementación de la lista de comandos y ficheros (e includes)

//Funciones vinculadas a los comandos de la shell
void exitShell(bool *term); //salir de la shell
void help(char *args); //imprime una ayuda al usuario
void authors(char *args); //Imprime el nombre y/o login de los autores
void printDate(); //Imprime la fecha del sistema en formato /DD/MM/YYYY
void printTime(); //Imprime la hora del sistema en formato hh:mm:ss
void pid(char *args); //Imprime el pid de la shell actual o padre
void changeDir(char* args); //Muestra la ruta actual o la cambia por la recibida en el parametro args
void hist(char* args, tList* lista); //Muestra/borra el historico de comandos
