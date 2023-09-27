//Cabecera de la lista (Usaremos la misma implementación para los comandos y los ficheros, por lo que habra funciones para cada tipo, y habŕa que controlar el no mezclarlos)
#include "p0_lib.h"
#define MAX_LEN_LIST 4096 //elementos maximos en una lista

//---Definicion de tipos---    

typedef char* tItemL//Cadena para guardar un comando / un directorio
typedef tItemL tLista[MAX_LEN_LIST]; //Definicion de la lista (Array de cadenas(punteros))


//---Funciones de la lista---

void createEmptyList(tLista* lista); //Inicializa una lista a vacia

//Inserta un comando a la lista en el indice n
//(Se presupone que los comandos estaran todos instertados al final y no habla eliminaciones por el medio)
bool insertComand(tLista* lista, char* cmd, int n); 

char * getCommand(tLista lista, int n); //Devuelve el comando numero n de una lista

//Inserta la información de un fichero
//(Se tiene en cuenta como el sistema asigna los fd)
bool insertFile(tLista* lista, char* path, int fd); 

void getFile(tLista lista, int fd); //Devuelve el nombre de un fichero dado su fd

//Borrar una lista entera.(Se presupone que solo aplica para listas de comandos) 
void deleteList(tLista* lista);

//Borra el fichero n de una lista (Los elementos no se desplazaran de su indice) 
//(Se presupone que no aplica para listas de comandos)
void deleteFile(tLista* lista, int fd); //El fd(file descriptor) se corresponde al indice del array
