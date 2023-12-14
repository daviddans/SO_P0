//Cabecera con las funciones de la practica 1

#include "p0_lib.h" // Incluir librerías de la practica anterior

void create(char* args, char** args_ptr); //Crear archivos o directorios
void showStat(char* args, char** args_ptr); //Muestra informacion de archivos o directorios
void list(char* args, char** args_ptr); //Lista los contenidos de un directorio
void delete(char* args); //Borra archivos o directorios vacios
void deltree(char* args, char** args_ptr); //Borra de forma recursiva archivos y directorios (FUNCION PEGRILOSA)

char* getNombre(char *path); //Funcion auxiliar para obtener el nombre de un archivo/directorio dada su ruta
char* getUser(uid_t uid); //Funcion auxiliar para obtener el nombre de usuario dado su id